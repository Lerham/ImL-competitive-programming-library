
// State は次の3つを持つ.
//   static State e();                                   // opの単位元
//   static State op(const State& left, const State& right);  // 区間の併合
//   static State make_leaf(Value x, int array_id);           // 必要なら葉を作る補助関数
//
// 使い方 (配列は1-indexed、queryは閉区間[l,r]).
//   SegmentTree<RangeBitQueryState> seg;
//   seg.init(N);
//   for (int i = 1; i <= N; i++) {
//       seg.update(i, RangeBitQueryState::make_leaf(A[i], i));
//   }
//   auto ans = seg.query(L, R);
//   auto x = ans.xor_value;
//   auto o = ans.or_value;
//   auto a = ans.and_value;
//
// RMQなら SegmentTree<RMQState> とし、ans.min(), ans.max() から情報を取る.
template <class State>
class SegmentTree {
   public:
    vector<State> dat;
    int siz = 1;  // sizは葉の個数となる2冪.

    // 2つのノードをまとめる演算. 詳細はState側で定義する.
    State op(const State& left, const State& right) {
        return State::op(left, right);
    }

    // op に対する単位元. 区間外のquery結果として使う.
    State e() { return State::e(); }

    // 要素datの初期化.
    void init(int N) {
        siz = 1;
        while (siz < N) {
            siz *= 2;  // sizはセグ木下部の要素数の上界となる2冪.
        }
        dat.assign(2 * siz, e());
    }

    //(1) array_idの要素をvalueに変えたとき, 他のセルを更新せよ.
    void update(int array_id, const State& value) {
        int cell_id = array_id + siz - 1;  // A[array_id] の"セグ木における"セル番号
        dat[cell_id] = value;               // array_idのいるセルをvalueに更新
        while (cell_id >= 2) {
            cell_id = cell_id / 2;  // 2で割ることで一つ上のセルに行く.
            dat[cell_id] = op(dat[cell_id * 2], dat[cell_id * 2 + 1]);  // 左下と右下をopとして更新.

            //(左下と右下のどっちかの値は手前の操作で更新済み)
        }
    }

    State get(int array_id) {
        int cell_id = array_id + siz - 1;  // A[array_id] の"セグ木における"セル番号
        return dat[cell_id];
    }

    // query: 閉区間[l,r]におけるStateを返す.
    //[l,r]が求めたい区間で, [a,b]がセルに対応する閉区間, cell_idは現在のセル番号
    State query(int l, int r, int a, int b, int cell_id) {
        if (r < a || b < l) {
            return e();
        }  // 全く含まれないときopに影響しない単位元を返す.
        if (l <= a && b <= r) {
            return dat[cell_id];
        }  // 完全に含まれているときdat[cell_id]を返す.
        // 部分的に覆ってる場合(一般の場合).
        int m = (a + b) / 2;
        State AnswerL = query(l, r, a, m, cell_id * 2);      // 左下でqueryを行った値を取得.
        State AnswerR = query(l, r, m + 1, b, cell_id * 2 + 1);  // 右下でqueryを行った値を取得.
        return op(AnswerL, AnswerR);
    }

    // 根の区間[1,siz]を指定する必要がない通常用の呼び出し.
    State query(int l, int r) { return query(l, r, 1, siz, 1); }
};
// Seg.query(l,r)で閉区間[l,r]のStateを取得.

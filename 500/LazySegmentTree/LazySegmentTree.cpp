// State は次を持つ.
//   static State e();
//   static State op(const State& left, const State& right);
//   static State apply(const State& state, const Lazy& action, int length);
//
// Lazy は次を持つ.
//   static Lazy e();
//   static bool is_id(const Lazy& action);
//   static Lazy compose(const Lazy& old_action, const Lazy& new_action);
// compose(old, new)は「oldを適用した後にnewを適用する」タグを返す.
//
// 使い方 (配列は1-indexed、区間は閉区間[l,r]).
//   LazySegmentTree<RangeAddSumState, RangeAddLazy> seg;
//   seg.init(N);
//   for (int i = 1; i <= N; i++) {
//       seg.update(i, RangeAddSumState::make_leaf(A[i], i));
//   }
//   seg.range_apply(L, R, {x});  // 閉区間[L,R]へxを加算
//   auto ans = seg.query(L, R);
template <class State, class Lazy>
class LazySegmentTree {
   public:
    vector<State> dat;
    vector<Lazy> lazy;
    int siz = 1;  // sizは葉の個数となる2冪.

    State op(const State& left, const State& right) {
        return State::op(left, right);
    }

    State e() { return State::e(); }

    // 要素datと遅延タグの初期化.
    void init(int N) {
        siz = 1;
        while (siz < N) {
            siz *= 2;  // sizはセグ木下部の要素数の上界となる2冪.
        }
        dat.assign(2 * siz, e());
        lazy.assign(2 * siz, Lazy::e());
    }

    //(1) array_idの要素をvalueに代入し, その経路の遅延タグを伝播して更新せよ.
    void update(int array_id, const State& value) {
        update(array_id, value, 1, siz, 1);
    }

    // 閉区間[l,r]にactionを適用する.
    void range_apply(int l, int r, const Lazy& action) {
        range_apply(l, r, action, 1, siz, 1);
    }

    // 閉区間[l,r]におけるStateを返す.
    State query(int l, int r) { return query(l, r, 1, siz, 1); }

   private:
    // cell_idの担当閉区間[a,b]全体にactionを適用する.
    void apply_to(int cell_id, int a, int b, const Lazy& action) {
        dat[cell_id] = State::apply(dat[cell_id], action, b - a + 1);
        lazy[cell_id] = Lazy::compose(lazy[cell_id], action);
    }

    // cell_idに溜まった遅延タグを子へ下ろす.
    void push(int cell_id, int a, int b) {
        if (a == b || Lazy::is_id(lazy[cell_id])) return;
        int m = (a + b) / 2;
        apply_to(cell_id * 2, a, m, lazy[cell_id]);
        apply_to(cell_id * 2 + 1, m + 1, b, lazy[cell_id]);
        lazy[cell_id] = Lazy::e();
    }

    void pull(int cell_id) {
        dat[cell_id] = op(dat[cell_id * 2], dat[cell_id * 2 + 1]);
    }

    void update(int array_id, const State& value, int a, int b, int cell_id) {
        if (a == b) {
            dat[cell_id] = value;
            lazy[cell_id] = Lazy::e();
            return;
        }
        push(cell_id, a, b);
        int m = (a + b) / 2;
        if (array_id <= m) {
            update(array_id, value, a, m, cell_id * 2);
        } else {
            update(array_id, value, m + 1, b, cell_id * 2 + 1);
        }
        pull(cell_id);
    }

    void range_apply(int l, int r, const Lazy& action, int a, int b, int cell_id) {
        if (r < a || b < l) return;
        if (l <= a && b <= r) {
            apply_to(cell_id, a, b, action);
            return;
        }
        push(cell_id, a, b);
        int m = (a + b) / 2;
        range_apply(l, r, action, a, m, cell_id * 2);
        range_apply(l, r, action, m + 1, b, cell_id * 2 + 1);
        pull(cell_id);
    }

    State query(int l, int r, int a, int b, int cell_id) {
        if (r < a || b < l) return e();
        if (l <= a && b <= r) return dat[cell_id];
        push(cell_id, a, b);
        int m = (a + b) / 2;
        State AnswerL = query(l, r, a, m, cell_id * 2);
        State AnswerR = query(l, r, m + 1, b, cell_id * 2 + 1);
        return op(AnswerL, AnswerR);
    }
};

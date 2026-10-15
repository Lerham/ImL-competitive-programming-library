// 自作State用の最小雛形.
// SegmentTree<CustomState> に渡して使う.
//
// このままでは「区間和」のStateとして動く.
// 新しい状態を作るときは、State名・持つフィールド・e/leaf/opを一緒に変える.
//
// 条件:
//   1. e() はopの単位元: op(e(), x) == x かつ op(x, e()) == x
//   2. op() は結合的: op(op(a, b), c) == op(a, op(b, c))
//   3. Stateの大きさは区間長によらず一定にする.
struct CustomState {
    using Value = long long;  // 葉に入れる値の型. 必要に応じて変更する.

    Value value;  // 区間を要約する情報. 複数必要ならstructのフィールドを増やす.

    // 空区間のState. opに影響しない値を返す.
    static CustomState e() {
        return {0};  // 区間和なら0、最小値ならINF、最大値なら-INF.
    }

    // 配列の1要素A[array_id] = xから、葉のStateを作る.
    static CustomState leaf(Value x, [[maybe_unused]] int array_id) {
        return {x};  // indexも必要ならarray_idをStateに入れる.
    }

    // 左右の区間Stateを1つの親Stateへまとめる.
    static CustomState op(const CustomState& left, const CustomState& right) {
        return {left.value + right.value};  // 区間和. 必要な合成処理へ変更する.
    }
};

// 使用例 (配列は1-indexed、queryは閉区間[l,r]).
//   SegmentTree<CustomState> seg;
//   seg.init(N);
//   for (int i = 1; i <= N; i++) {
//       seg.update(i, CustomState::leaf(A[i], i));
//   }
//   auto result = seg.query(L, R);
//   cout << result.value << '\n';

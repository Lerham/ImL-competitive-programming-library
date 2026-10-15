// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/500/LazySegmentTree/RangeAddMaxState.cpp
// 区間加算・区間最大値用のStateと遅延タグ.
struct RangeAddMaxLazy {
    long long add;

    static RangeAddMaxLazy e() { return {0}; }
    static bool is_id(const RangeAddMaxLazy& action) { return action.add == 0; }
    static RangeAddMaxLazy compose(const RangeAddMaxLazy& old_action,
                                   const RangeAddMaxLazy& new_action) {
        return {old_action.add + new_action.add};
    }
};

struct RangeAddMaxState {
    long long max_value;

    static RangeAddMaxState e() { return {-(1LL << 60)}; }
    static RangeAddMaxState make_leaf(long long x, int array_id) { return {x}; }
    static RangeAddMaxState op(const RangeAddMaxState& left, const RangeAddMaxState& right) {
        return {left.max_value > right.max_value ? left.max_value : right.max_value};
    }
    static RangeAddMaxState apply(const RangeAddMaxState& state,
                                  const RangeAddMaxLazy& action, int length) {
        return {state.max_value + action.add};
    }
};

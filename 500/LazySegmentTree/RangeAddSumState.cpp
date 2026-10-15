// 区間加算・区間和用のStateと遅延タグ.
struct RangeAddLazy {
    long long add;

    static RangeAddLazy e() { return {0}; }
    static bool is_id(const RangeAddLazy& action) { return action.add == 0; }
    static RangeAddLazy compose(const RangeAddLazy& old_action, const RangeAddLazy& new_action) {
        return {old_action.add + new_action.add};
    }
};

struct RangeAddSumState {
    long long sum;

    static RangeAddSumState e() { return {0}; }
    static RangeAddSumState make_leaf(long long x, int array_id) { return {x}; }
    static RangeAddSumState op(const RangeAddSumState& left, const RangeAddSumState& right) {
        return {left.sum + right.sum};
    }
    static RangeAddSumState apply(const RangeAddSumState& state, const RangeAddLazy& action, int length) {
        return {state.sum + action.add * length};
    }
};

// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/400/SegmentTree/States/RProdQState.cpp
// Range Product Query用の状態.
// modintを使う場合はlong longをmintに置き換える.
struct RProdQState {
    long long value;

    static RProdQState e() { return {1}; }
    static RProdQState make_leaf(long long x, int array_id) { return {x}; }
    static RProdQState op(const RProdQState& left, const RProdQState& right) {
        return {left.value * right.value};
    }
};

// Range Sum Query用の状態.
struct RSQState {
    long long sum;

    static RSQState e() { return {0}; }
    static RSQState make_leaf(long long x, int array_id) { return {x}; }
    static RSQState op(const RSQState& left, const RSQState& right) {
        return {left.sum + right.sum};
    }
};

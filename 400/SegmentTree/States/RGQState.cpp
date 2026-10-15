// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/400/SegmentTree/States/RGQState.cpp
// Range GCD Query用の状態.
struct RGQState {
    long long value;

    static RGQState e() { return {0}; }
    static RGQState make_leaf(long long x, int array_id) { return {x}; }
    static RGQState op(const RGQState& left, const RGQState& right) {
        return {gcd(left.value, right.value)};
    }
};

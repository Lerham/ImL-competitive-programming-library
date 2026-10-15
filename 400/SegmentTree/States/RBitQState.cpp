// Range Bit Query用の状態.
// OR・AND・XORをまとめて保持し、1回のqueryでどれも取得できる.
// SegmentTree<RangeBitQueryState> に渡して使う.
struct RangeBitQueryState {
    unsigned long long or_value;
    unsigned long long and_value;
    unsigned long long xor_value;

    static RangeBitQueryState e() {
        return {0, numeric_limits<unsigned long long>::max(), 0};
    }
    static RangeBitQueryState make_leaf(unsigned long long x, int array_id) {
        return {x, x, x};
    }
    static RangeBitQueryState op(const RangeBitQueryState& left, const RangeBitQueryState& right) {
        return {left.or_value | right.or_value,
                left.and_value & right.and_value,
                left.xor_value ^ right.xor_value};
    }
};

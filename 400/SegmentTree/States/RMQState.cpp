// Range Min/Max Query用の状態.
// 最小値・最大値それぞれについて、個数と最左・最右の位置も追跡する.
struct RMQState {
    struct Info {
        int value;
        int count;
        int first_index;
        int last_index;
    };

    Info min_info;
    Info max_info;

    static Info min_e() {
        return {numeric_limits<int>::max(), 0, numeric_limits<int>::max(), numeric_limits<int>::min()};
    }
    static Info max_e() {
        return {numeric_limits<int>::min(), 0, numeric_limits<int>::max(), numeric_limits<int>::min()};
    }

    static Info op_min(const Info& left, const Info& right) {
        if (left.value < right.value) return left;
        if (left.value > right.value) return right;
        return {left.value,
                left.count + right.count,
                std::min(left.first_index, right.first_index),
                std::max(left.last_index, right.last_index)};
    }

    static Info op_max(const Info& left, const Info& right) {
        if (left.value > right.value) return left;
        if (left.value < right.value) return right;
        return {left.value,
                left.count + right.count,
                std::min(left.first_index, right.first_index),
                std::max(left.last_index, right.last_index)};
    }

    static RMQState e() { return {min_e(), max_e()}; }
    static RMQState make_leaf(int x, int array_id) {
        Info info = {x, 1, array_id, array_id};
        return {info, info};
    }
    static RMQState op(const RMQState& left, const RMQState& right) {
        return {op_min(left.min_info, right.min_info), op_max(left.max_info, right.max_info)};
    }

    const Info& min() const { return min_info; }
    const Info& max() const { return max_info; }
};

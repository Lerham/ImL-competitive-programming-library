// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/main/Geometry/argument_sort.cpp
// 000/starter.cpp の include と型定義を前提とする。
// 1-indexed の整数座標を、正の x 軸から反時計回りに偏角順で返す。
// 原点は偏角を持たないため先頭に置く。同じ偏角の点は入力順を保つ。
// x[0], y[0] はダミーとしてそのまま返す。x と y は同じサイズで空でないこと。
// T は 64 bit 以下の符号付き整数型。計算量 O(N log N)。
template <class T>
pair<vector<T>, vector<T>> argument_sort(
    const vector<T>& x, const vector<T>& y) {
    static_assert(is_integral_v<T> && is_signed_v<T> && sizeof(T) <= 8,
                  "coordinates must be signed integers of at most 64 bits");
    assert(!x.empty() && x.size() == y.size());

    vector<size_t> order(x.size() - 1);
    iota(order.begin(), order.end(), size_t{1});
    const auto region = [&](size_t i) {
        if (x[i] == 0 && y[i] == 0) return 0;
        return (y[i] > 0 || (y[i] == 0 && x[i] > 0)) ? 1 : 2;
    };
    stable_sort(order.begin(), order.end(), [&](size_t a, size_t b) {
        int ra = region(a), rb = region(b);
        if (ra != rb) return ra < rb;
        if (ra == 0) return false;
        // 差を取らずに比較することで、long long の全範囲でも溢れない。
        return static_cast<__int128>(x[a]) * y[b] >
               static_cast<__int128>(y[a]) * x[b];
    });

    vector<T> sorted_x{x[0]}, sorted_y{y[0]};
    sorted_x.reserve(x.size());
    sorted_y.reserve(y.size());
    for (size_t i : order) {
        sorted_x.push_back(x[i]);
        sorted_y.push_back(y[i]);
    }
    return {move(sorted_x), move(sorted_y)};
}

// a^k <= n かをオーバーフローせずに判定
bool power_leq(ll a, int k, ll n) {
    __int128 value = 1;

    for (int i = 0; i < k; i++) {
        value *= a;

        if (value > n) {
            return false;
        }
    }

    return true;
}

// floor(n^(1/k)) を返す
// 1 <= n <= 1e18, 1 <= k を想定
ll root(int k, ll n) {
    ll ok = 0;      // ok^k <= n
    ll ng = n + 1;  // ng^k > n

    while (ng - ok > 1) {
        ll mid = ok + (ng - ok) / 2;

        if (power_leq(mid, k, n)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }

    return ok;
}

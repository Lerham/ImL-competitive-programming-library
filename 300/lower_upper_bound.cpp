// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/main/300/lower_upper_bound.cpp
// 000/starter.cpp を前提とする。詳しい使い方は lower_upper_bound.md を参照。
// x[1] ... x[N] が昇順、x[0] はダミー、x.size() == N + 1。
// 配列は空でもよい（その場合 x.size() == 1）。

// x[i] >= value を満たす最小の i。存在しなければ N + 1。
ll lower_bound_index(const vector<ll>& x, ll value) {
    return lower_bound(x.begin() + 1, x.end(), value) - x.begin();
}

// x[i] > value を満たす最小の i。存在しなければ N + 1。
ll upper_bound_index(const vector<ll>& x, ll value) {
    return upper_bound(x.begin() + 1, x.end(), value) - x.begin();
}

/*
よく使う書き方（N = (ll)x.size() - 1、x[1..N] は昇順）

ll lb = lower_bound_index(x, value); // x[i] >= value の最小 i。なければ N + 1
ll ub = upper_bound_index(x, value); // x[i] >  value の最小 i。なければ N + 1

ll ge = lb;       // x[i] >= value の最小 i
ll gt = ub;       // x[i] >  value の最小 i
ll lt = lb - 1;   // x[i] <  value の最大 i。なければ 0
ll le = ub - 1;   // x[i] <= value の最大 i。なければ 0

ll count_lt = lb - 1;      // x[i] <  value の個数
ll count_le = ub - 1;      // x[i] <= value の個数
ll count_eq = ub - lb;     // x[i] == value の個数
ll count_ge = N + 1 - lb;  // x[i] >= value の個数
ll count_gt = N + 1 - ub;  // x[i] >  value の個数

// 見つかったときだけ x[i] にアクセスする。
if (ge <= N) { ll answer = x[ge]; }
if (le >= 1) { ll answer = x[le]; }

// L <= R のとき、L <= x[i] <= R の個数。
ll count_closed = upper_bound_index(x, R) - lower_bound_index(x, L);
*/

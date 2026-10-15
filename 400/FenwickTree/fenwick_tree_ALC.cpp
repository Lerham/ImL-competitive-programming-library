// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/400/FenwickTree/fenwick_tree_ALC.cpp
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;
using Graph = vector<vector<int>>;
using Matrix = vector<vector<long long>>;
const int inf = 1 << 30;
const ll INF = 1LL << 60;
const ld pi = acosl(-1.0L);
using mint = atcoder::modint998244353;

//   fw.add(x,1);        // 値 x をbitに追加
//   int ans = fw_lower_bound(v);
//   → 小さい順で v 番目の値が返る
//
// 計算量: O(log n)

int fw_lower_bound(int w) {
    int x = 0;
    int k = 1;

    while ((k << 1) <= n) k *= 2;  // n 以下の最大の2冪

    for (; k > 0; k >>= 1) {
        if (x + k <= n && bit[x + k] < w) {
            w -= bit[x + k];
            x += k;
        }
    }

    return x + 1;
}

int main() {
    int N, Q;
    cin >> N >> Q;
    fenwick_tree<ll> fw_a(N);
    for (int i = 0; i < N; i++) {
        ll a;
        cin >> a;
        fw_a.add(i, a);  // a[i] を fenwick tree に追加
    }

    for (int q = 0; q < Q; q++) {
        int query;
        cin >> query;
        if (query == 0) {
            int p;
            ll x;
            cin >> p >> x;
            fw_a.add(p, x);  // a[p] を +x する
        } else if (query == 1) {
            int l, r;
            cin >> l >> r;
            cout << fw_a.sum(l, r) << endl;  // a[l] + ... + a[r-1] を出力
        }
    }
}

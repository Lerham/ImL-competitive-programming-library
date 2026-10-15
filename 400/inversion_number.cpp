// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/400/inversion_number.cpp
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
// MOD
const ll mod = 998244353;
using mint = atcoder::modint998244353;

void YesNo(bool ok) { cout << (ok ? "Yes" : "No") << '\n'; }

ll inversion_number(const vector<ll>& P) {
    // 前提: P は 1-indexed であり, P の要素は 0 以上 N 以下の整数の置換である.
    int N = (int)P.size() - 1;  // P は 1-indexed であると仮定
    fenwick_tree<ll> fw(N + 1);

    ll inv = 0;

    for (int i = 1; i <= N; i++) {
        // P[i] より大きいこれまでに現れた要素の個数
        inv += (i - 1) - fw.sum(0, P[i] + 1);  //[P[i]+1, N]上の和

        fw.add(P[i], 1);
    }

    return inv;
}

int main() {
    int N;
    cin >> N;
    vector<ll> P(N + 1);
    for (int i = 1; i <= N; i++) cin >> P[i];

    cout << inversion_number(P) << endl;  // O(NlogN)
}

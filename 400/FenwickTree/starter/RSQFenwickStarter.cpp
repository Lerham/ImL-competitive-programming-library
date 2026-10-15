// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/400/FenwickTree/starter/RSQFenwickStarter.cpp
#include <bits/stdc++.h>
#include <ostream>
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
// const ll mod = 1000000007;
// using mint = atcoder::modint1000000007;

#define rep(i, n) for (int i = 1; i <= (n); i++)
#define reps(i, l, r) for (int i = (l); i <= (r); i++)
#define rrep(i, n) for (int i = (n); i >= 1; i--)

// Debug用
constexpr bool do_debug = false;
vector<string> debug_log;
#define debug(x)                            \
    do {                                    \
        if (do_debug) {                     \
            ostringstream oss;              \
            oss << #x << " = " << (x);      \
            debug_log.push_back(oss.str()); \
        }                                   \
    } while (false)

void print_debug_log() {
    if (!do_debug) return;
    cout << "\n========== DEBUG ==========\n";
    for (const string& s : debug_log) cout << s << '\n';
    cout << "===========================\n";
}

void printyn(bool ok) { cout << (ok ? "Yes" : "No") << '\n'; }

ll N, M, Q, T;
vll A(500009);
string S;
int H, W;
vector<string> grid(300009);

// Fenwick Tree (Binary Indexed Tree)
// 配列の添字は 1-indexed、区間は閉区間 [l, r]。
// add(p, x): A[p] に x を加算                 O(log N)
// sum(r):    A[1] + ... + A[r]               O(log N)
// sum(l, r): A[l] + ... + A[r]               O(log N)
// 点の値を置き換える場合は、現在値との差分を add する。
struct FenwickTree {
    int n = 0;
    vector<ll> bit;

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);  // bit[1..n] を使用
    }

    // 配列 a (1-indexed、a[0] は未使用) で初期化: O(N)
    void build(const vector<ll>& a) {
        assert(!a.empty());
        init((int)a.size() - 1);
        for (int i = 1; i <= n; i++) {
            bit[i] += a[i];
            int parent = i + (i & -i);
            if (parent <= n) bit[parent] += bit[i];
        }
    }

    // A[p] += x (p は 1-indexed)
    void add(int p, ll x) {
        assert(1 <= p && p <= n);
        for (int i = p; i <= n; i += i & -i) bit[i] += x;
    }

    // [1, r] の和
    ll sum(int r) const {
        assert(0 <= r && r <= n);
        ll result = 0;
        for (int i = r; i > 0; i -= i & -i) result += bit[i];
        return result;
    }

    // [l, r] の和
    ll sum(int l, int r) const {
        assert(1 <= l && l <= r && r <= n);
        return sum(r) - sum(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    FenwickTree fw;
    fw.build(a);

    // クエリ例
    // 0 p x: A[p] += x (p は 1-indexed)
    // 1 l r: [l, r] の区間和を出力
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p;
            ll x;
            cin >> p >> x;
            fw.add(p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << fw.sum(l, r) << '\n';
        }
    }

    print_debug_log();
}

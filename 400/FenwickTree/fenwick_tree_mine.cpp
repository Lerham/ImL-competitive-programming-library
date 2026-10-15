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

// 加算: op(a, b) = a + b, e() = 0, inv(a) = -a
template <class T> T fw_add(T a, T b) { return a + b; }
template <class T> T fw_zero() { return T(0); }
template <class T> T fw_neg(T a) { return -a; }

// xor: op(a, b) = a ^ b, e() = 0, inv(a) = a
template <class T> T fw_xor(T a, T b) { return a ^ b; }
template <class T> T fw_self(T a) { return a; }

// 乗算: 非零の modint 用。整数の除算では逆元を表せないので使わない。
// modint998244353 では初期値・更新値ともに 0 を禁止する。
mint fw_mul(mint a, mint b) {
    assert(a.val() != 0 && b.val() != 0);
    return a * b;
}
mint fw_one() { return mint(1); }
mint fw_reciprocal(mint a) { return a.inv(); }

// op は結合則・交換則を満たすこと（可換群）。
// e は単位元、inv は逆元: op(a, e()) = a, op(a, inv(a)) = e()。
// 自作の演算: FenwickTree<T, op, e, inv> fw(n);
// 添字は 0-indexed、区間は半開区間 [l, r)。更新・取得は O(log n)。
template <class T, T (*op)(T, T) = fw_add<T>,
          T (*e)() = fw_zero<T>, T (*inv)(T) = fw_neg<T>>
struct FenwickTree {
    int n;
    vector<T> bit;

    FenwickTree(int n) : n(n), bit(n + 1, e()) {}

    FenwickTree(const vector<T>& a) : FenwickTree((int)a.size()) {
        for (int i = 0; i < n; i++) {
            add(i, a[i]);
        }
    }

    // a[p] = op(a[p], x)（代入ではない）
    void add(int p, T x) {
        assert(0 <= p && p < n);
        p++;  // 内部は1-indexed
        while (p <= n) {
            bit[p] = op(bit[p], x);
            p += p & -p;
        }
    }

    // [0, r) の集約。空区間なら e()。
    T prod(int r) const {
        assert(0 <= r && r <= n);
        T res = e();

        while (r > 0) {
            res = op(res, bit[r]);
            r -= r & -r;
        }

        return res;
    }

    // [l, r) の集約。prefix(r) から prefix(l) を逆元で取り除く。
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return op(prod(r), inv(prod(l)));
    }

    // 既存の加算・xor の呼び出しとも互換。
    T sum(int r) const { return prod(r); }
    T sum(int l, int r) const { return prod(l, r); }

    // sum(0, i+1) >= w となる最小のi
    // 存在しなければn。w <= 0 なら 0。
    // 標準の加算のみ対応。各 a[i] >= 0 で累積和が単調であること。
    int lower_bound(T w) const {
        static_assert(op == fw_add<T> && e == fw_zero<T> && inv == fw_neg<T>,
                      "lower_bound is only supported for the default addition");
        if (w <= 0) return 0;

        int x = 0;
        int k = 1;

        while (k <= n / 2) {
            k *= 2;
        }

        for (; k > 0; k /= 2) {
            int nx = x + k;

            if (nx <= n && bit[nx] < w) {
                w -= bit[nx];
                x = nx;
            }
        }

        return x;
    }
};


template <class T>
using FenwickTree_XOR = FenwickTree<T, fw_xor<T>, fw_zero<T>, fw_self<T>>;
using FenwickTree_MUL = FenwickTree<mint, fw_mul, fw_one, fw_reciprocal>;

int main() {
    vector<ll> A = {10, 20, 30};
    FenwickTree<ll> fw(A);
    FenwickTree_XOR<ll> fw_xor(A);
    FenwickTree_MUL fw_mul(vector<mint>{10, 20, 30});

    fw.prod(0, 3);      // 10 + 20 + 30 = 60
    fw_xor.prod(0, 2);  // 10 ^ 20 = 30
    fw_mul.prod(1, 3);  // 20 * 30 = 600 (mod 998244353)

    fw.add(1, 5);      // a[1] += 5
    fw_xor.add(1, 5);  // a[1] ^= 5
    fw_mul.add(1, 5);  // a[1] *= 5

    fw.lower_bound(35);  // 1（10 + 25 >= 35）
    return 0;
}

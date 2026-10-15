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
//const ll mod = 1000000007;
//using mint = atcoder::modint1000000007;

#define rep(i,n) for(int i=1;i<=n;i++)
#define reps(i,l,r) for(int i=(l);i<=(r);i++)
#define rrep(i,n) for(int i=(n);i>=1;i--)

void printyn(bool ok) { cout << (ok ? "Yes" : "No") << endl; }

ll N, M, Q; 
string S; 
int H,W; 
vector<string> grid(300009);

template <class T>
struct FenwickTree_XOR {
    int n;
    vector<T> bit;

    FenwickTree_XOR(int n) : n(n), bit(n + 1, 0) {}

    FenwickTree_XOR(const vector<T>& a) {
        n = (int)a.size();
        bit.assign(n + 1, 0);

        for (int i = 0; i < n; i++) {
            add(i, a[i]);
        }
    }

    // a[p] ^= x
    void add(int p, T x) {
        p++;  // 内部は1-indexed
        while (p <= n) {
            bit[p] ^= x;
            p += p & -p;
        }
    }

    // a[0] ^ ... ^ a[r-1]
    T sum(int r) const {
        T res = 0;

        while (r > 0) {
            res ^= bit[r];
            r -= r & -r;
        }

        return res;
    }

    // a[l] ^ ... ^ a[r-1]
    T sum(int l, int r) const { return sum(r) ^ sum(l); }

    // sum(0, i+1) >= w となる最小のi
    // 存在しなければn
    int lower_bound(T w) const {
        if (w <= 0) return 0;

        int x = 0;
        int k = 1;

        while (k * 2 <= n) {
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


int main() {
    cin >> N >> Q; 
    vll A(N+1); 
    rep(i, N) cin >> A[i];
    vll T(Q+1), X(Q+1), Y(Q+1);
    rep(i, Q) {cin >> T[i] >> X[i] >> Y[i];
    }

    FenwickTree_XOR<ll> fw_xor(A);
    rep(i, Q) {
        if(T[i] == 1) {
            fw_xor.add(X[i], Y[i]);
        }
        else{
            cout << fw_xor.sum(X[i], Y[i]+1) << endl;
        }
    }

}

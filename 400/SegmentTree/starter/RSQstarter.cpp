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
constexpr bool do_debug = false;  // 提出前に false
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

void printyn(bool ok) { cout << (ok ? "Yes" : "No") << endl; }

ll N, M, Q, T;
vll A(500009);
string S;
int H, W;
vector<string> grid(300009);

// ================================================================
// Segment Tree を使う問題では、この CustomState だけを編集する。
// 今は「区間和」を返す RSQ の State。
//
// e()    : 空区間の値。op の単位元。
// leaf() : 配列の 1 要素から葉の State を作る。
// op()   : 左右 2 区間の State を結合する。
//
// index も答えに必要なら、State の field に持たせて leaf/op で更新する。
// 例: 最小値・個数・最左 index を持つ RMQState。
// ================================================================
// Range Sum Query用の状態.
struct RSQState {
    long long sum;

    static RSQState e() { return {0}; }

    // A[array_id] から葉の State を作る
    static RSQState leaf(long long x, int array_id) { return {x}; }

    static RSQState op(const RSQState& left, const RSQState& right) {
        return {left.sum + right.sum};
    }
};

// 配列は 1-indexed。query(l, r) は閉区間 [l, r]。
template <class State>
class SegmentTree {
   private:
    int siz = 1;
    vector<State> dat;

    State query(int l, int r, int a, int b, int cell_id) const {
        if (r < a || b < l) return State::e();
        if (l <= a && b <= r) return dat[cell_id];

        int m = (a + b) / 2;
        return State::op(query(l, r, a, m, cell_id * 2), query(l, r, m + 1, b, cell_id * 2 + 1));
    }

   public:
    void init(int n) {
        siz = 1;
        while (siz < n) siz *= 2;
        dat.assign(2 * siz, State::e());
    }

    // A[array_id] を value に更新する。array_id は 1-indexed。
    void update(int array_id, const State& value) {
        int cell_id = array_id + siz - 1;
        dat[cell_id] = value;
        while (cell_id >= 2) {
            cell_id /= 2;
            dat[cell_id] = State::op(dat[cell_id * 2], dat[cell_id * 2 + 1]);
        }
    }

    State get(int array_id) const { return dat[array_id + siz - 1]; }

    // 閉区間 [l, r] の State を返す。
    State query(int l, int r) const { return query(l, r, 1, siz, 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    // vll A(N + 1);
    vll T(Q + 1);            // query番号
    vll X(Q + 1), Y(Q + 1);  // (pos, x) or (l, r)

    // rep(i, N) cin >> A[i];
    rep(i, Q) cin >> T[i] >> X[i] >> Y[i];

    SegmentTree<RSQState> seg;
    seg.init(N);
    rep(i, N) { seg.update(i, RSQState::leaf(A[i], i)); }

    rep(i, Q) {
        if (T[i] == 1) {
            A[X[i]] = Y[i];
            seg.update(X[i], RSQState::leaf(A[X[i]], X[i]));
        } else {
            int l = X[i];
            int r = Y[i];
            auto result = seg.query(l, r-1);  // 閉区間 [l, r]
            cout << result.sum << endl;
        }
    }

    // main の最後で一括表示
    print_debug_log();
}

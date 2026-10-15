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
// const ll mod = 1000000007;
// using mint = atcoder::modint1000000007;

#define rep(i, n) for (ll i = 1; i <= n; i++)
#define reps(i, l, r) for (ll i = (l); i <= (r); i++)
#define rrep(i, n) for (ll i = (n); i >= 1; i--)

constexpr bool do_debug = true;  //@@@@@@@@@@@@@@@@ 提出前にFalse @@@@@@@@@@@@@@@@@@@@
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
    for (const string& s : debug_log) {
        cout << s << '\n';
    }
    cout << "===========================\n";
}
void printyn(bool ok) { cout << (ok ? "Yes" : "No") << endl; }



// 二分探索
bool P_bs(int x) {
    // xが条件を満たすかどうか
    // P(left) = false, P(right) = true
    // TODO
    bool Dummy = (x == 0);
    return Dummy;
}

int meguru_search(int l, int r) {
    // 探索対象：l, l+1, ..., r
    int left = l - 1;   // 条件を満たさない番兵
    int right = r + 1;  // 条件を満たす番兵

    while (right - left > 1) {
        int mid = left + (right - left) / 2;

        if (P_bs(mid))
            right = mid;
        else
            left = mid;
    }

    // 条件を満たす最小の位置
    // 存在しなければ N + 1
    return right;
}

void diagnosis_lbub(const vector<int>& A, int x, int L, int R) {
    // 診断用関数: Aの[L,R]の範囲でx未満およびx以下の要素の個数を表示する
    cout << "====Diagnosing_lbub for x = " << x << " in A[" << L << "," << R
         << "]:" << "====" << endl;
    cout << "is_sorted = " << boolalpha << is_sorted(A.begin() + L, A.begin() + R + 1) << '\n';
    int pos_l = lower_bound(A.begin() + L, A.begin() + R + 1, x) - A.begin();
    int pos_u = upper_bound(A.begin() + L, A.begin() + R + 1, x) - A.begin();

    // 小さい範囲でAを見る
    if (R - L + 1 <= 20) {
        cout << "A[" << L << "," << R << "] = ";

        for (int i = L; i <= R; i++) {
            cout << A[i] << ' ';
        }

        cout << '\n';
    }
    cout << "(lb, ub) = (" << pos_l << ", " << pos_u << ")" << endl;

    if (pos_l <= R)
        cout << "A[lower_bound] = " << A[pos_l] << '\n';
    else
        cout << "A[lower_bound] = 範囲内に存在しない\n";

    if (pos_u <= R)
        cout << "A[upper_bound] = " << A[pos_u] << '\n';
    else
        cout << "A[upper_bound] = 範囲内に存在しない\n";

    if (pos_u > L)
        cout << "A[upper_bound - 1] = " << A[pos_u - 1] << '\n';
    else
        cout << "A[upper_bound - 1] = 範囲内に存在しない\n";

    cout << "x未満の個数 = " << pos_l - L << '\n';
    cout << "x以下の個数 = " << pos_u - L << '\n';
    cout << "xと等しい個数 = " << pos_u - pos_l << '\n';

    cout << "========================\n";
}

// ----RunLengthEncoding----
vector<pair<char, int>> rle(const string& S) {
    vector<pair<char, int>> res;
    for (char c : S) {
        if (res.empty() || res.back().first != c) {
            res.push_back({c, 1});
        } else {
            res.back().second++;
        }
    }
    return res;
}

// // 尺取り法でi (通常はr+1) を含めてよいかの判定関数
// bool P_tp(int N, const vector<int>& A, int i, int kinds, map<int, int>& cnt) {
//     // iを含めて種類数がK以下を維持できるかを判定
//     bool Kinds_stay = (i <= N && (cnt[A[i]] > 0 || kinds < K));
//     // iを含めて全て異なるかの判定
//     bool All_distinct = (i <= N && cnt[A[i]] == 0);
//     // iを含めてK以下の回数しか出現していないかの判定
//     bool AtMostK_Occur = (i <= N && cnt[A[i]] < K);
//     return Kinds_stay;
// }

map<string, ll> two_pointer(const vector<int>& A, int N) {
    // 前準備 (1-indexed 前提)
    int l = 1, r = l;   // 区間[l,r]を管理 (1-indexed 前提)
    map<int, int> cnt;  // 要素の出現回数を管理するマップ
    cnt[A[1]] = 1;      // 区間[1,1]を見た
    int max_kinds = 1;
    int online_kinds = 1;

        // [&]によりN, A, cnt, online_kinds, Kを参照できる
    auto P_tp = [&](int i) -> bool {
        if (i > N) return false;
        // ======== A[i] を区間へ追加しても条件を満たすか ========


        // ====================================================

        // 異なる値がK種類以下
        // return cnt[A[i]] > 0 || online_kinds < K;

        // 全要素が異なる
        // return cnt[A[i]] == 0;

        // 各値の出現回数がK回以下
        // return cnt[A[i]] < K;
        return false;
    };

    int max_length = 0;   // 条件を満たす最大の長さを格納する変数
    ll cnt_interval = 0;  // 条件を満たす区間の個数
    ll sum_length = 0;    // 条件を満たす全区間の長さの総和
    int max_l = -1;
    int max_r = -1;
    while (l <= N && r <= N) {
        // [l, r] は条件を満たしている前提
        if (r - l + 1 > max_length) {
            max_length = r - l + 1;
            max_l = l;
            max_r = r;
        }
        // debug(l);
        // debug(r);
        // debug(kinds);

        // r+1を含めるかどうかの判定
        bool Is_next_r_ok = P_tp(r + 1);

        if (Is_next_r_ok) {
            // ----r+1を区間に含める----
            cnt[A[r + 1]]++;
            if (cnt[A[r + 1]] == 1)
                online_kinds++;  // 区間に新しい要素が追加されたので種類数を増やす
            max_kinds = max(max_kinds, online_kinds);
            r++;
        } else {
            cnt_interval += r - l + 1;
            // debug(cnt_interval);
            sum_length += 1LL * (r - l + 1) * (r - l + 2) / 2;
            // debug(sum_length);
            // ----lを見る範囲から抜く----
            cnt[A[l]]--;
            if (cnt[A[l]] == 0) {
                online_kinds--;  // 区間から要素が消えたので種類数を減らす
            }
            l++;  // 左端を一つ進める
        }
    }
    map<string, ll> two_pointer_info;
    two_pointer_info["max_length"] = max_length;      // 条件を満たす区間の最大長
    two_pointer_info["max_l"] = max_l;                // 最大区間の左端
    two_pointer_info["max_r"] = max_r;                // 最大区間の右端
    two_pointer_info["cnt_interval"] = cnt_interval;  // 条件を満たす区間数
    two_pointer_info["sum_length"] = sum_length;      // 条件を満たす全区間の長さの総和 (仮の値)
    two_pointer_info["max_kinds"] = max_kinds;        // 区間内の最大種類数
    return two_pointer_info;                          // 条件を満たす最大の長さを返す
}

//累積和
vector<ll> prefix_sum(const vector<int>& A) {
    int N = A.size() - 1;  // 1-indexed 前提
    vector<ll> C(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        C[i] = C[i - 1] + A[i];
    }
    return C;
}

//==================
// 基本変数
ll N, M, Q, K;
vll A(500009);
string S;
int H, W;
vector<string> grid(300009);
//==================

// @@@@@@@@@@@ solve @@@@@@@@@@@
int main() {
    vector<int> A = {0, 1, 1, 2, 2, 2, 3, 3, 5, 8, 10};
    diagnosis_lbub(A, 2, 1, A.size() - 1);

    string S = "aaabbcccc";
    auto v = rle(S);

    // v = {{'a', 3}, {'b', 2}, {'c', 4}}
}

// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/300/two_pointer.cpp
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
const ll mod = 1000000007;
using mint = atcoder::modint1000000007;

// Debug用
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

void YesNo(bool ok) { cout << (ok ? "Yes" : "No") << '\n'; }

// 尺取り法でi (通常はr+1) を含めてよいかの判定関数
bool P_tp(int N, const vector<int>& A, , int i, int kinds, map<int, int>& cnt) {
    // iを含めて種類数がK以下を維持できるかを判定
    bool Kinds_stay = (i <= N && (cnt[A[i]] > 0 || kinds < K));
    // iを含めて全て異なるかの判定
    bool All_distinct = (i <= N && cnt[A[i]] == 0);
    // iを含めてK以下の回数しか出現していないかの判定
    bool AtMostK_Occur = (i <= N && cnt[A[i]] < K);
    return Kinds_stay;
}

map<string, ll> two_pointer(const vector<int>& A, , int N) {
    // 前準備 (1-indexed 前提)
    int l = 1, r = l;   // 区間[l,r]を管理 (1-indexed 前提)
    map<int, int> cnt;  // 要素の出現回数を管理するマップ
    cnt[A[1]] = 1;      // 区間[1,1]を見た
    int max_kinds = 1;
    int online_kinds = 1;

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
        bool Is_next_r_ok = P_tp(N, A, r + 1, online_kinds, cnt);

        if (Is_next_r_ok) {
            // ----r+1を区間に含める----
            cnt[A[r + 1]]++;
            if (cnt[A[r + 1]] == 1)
                online_kinds++;  // 区間に新しい要素が追加されたので種類数を増やす
            max_kinds = max(max_kinds, online_kinds);
            r++;
        } else {
            cnt_interval += r - l + 1;
            sum_length += 1LL * (r - l + 1) * (r - l + 2) / 2;

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

int main() {
    map<int, int> cnt;  // 要素の出現回数を管理するマップ
    int N;
    int K;
    cin >> N >> K;
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    auto res = two_pointer(A, N);
    cout << res["max_length"] << '\n';
}

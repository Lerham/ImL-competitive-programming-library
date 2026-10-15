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

void YesNo(bool ok) { cout << (ok ? "Yes" : "No") << endl; }

int N;
vector<pair<int, int>> intervals;  // 閉区間[l, r]

int solve_Interval_Scheduing(vector<pair<int, int>> intervals) {
    // intervals は閉区間[l, r]のリストで1-indexedとする
    sort(intervals.begin(), intervals.end());

    int ansval = 0;  // 選べる区間の数の最大値
    int size = intervals.size();
    intervals[0] = {-inf, -inf};
    intervals.push_back({inf, inf});

    int seen = 0;

    for (int i = 1; i < size; i++) {
        bool can_choose = intervals[i].first > intervals[seen].second;  // 見てた区間は選べるか
        bool should_replace =
            intervals[i].second <
            intervals[seen].second;  // seen区間よりも区間iが速く終わる場合に乗り換え
        string message;
        if (can_choose) {  // 見てる区間と被らない場合
            seen = i;
            ansval++;  // 見てた区間を選んだのでカウント
            message = "次に見る区間";
        } else {
            if (should_replace) {
                seen = i;
                message = "乗り換えた区間";
            }
            message = "スキップした区間";
        }
        // DEBUG: 選択状況を出力
        //  cout << message << ": [" << intervals[i].first << ", " << intervals[i].second << "]"
        //           << endl;
    }
    return ansval;
}

int main() {
    int N;
    cin >> N;
    vector<pii> intervals(N + 1, {0, 0});
    for (int i = 1; i <= N; i++) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    cout << solve_Interval_Scheduing(intervals);
}

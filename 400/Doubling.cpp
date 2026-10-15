// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/400/Doubling.cpp
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
struct Doubling
{
    const int MAX_LOG = 60;    // K が 1e18 まで行ける想定
    int N;                     // A のサイズ
    vector<vector<int>> table; // table[k][i] = i から 2^k 回後

    // ===== 準備：A からダブリング表を作る =====
    Doubling(const vector<int> &A)
    {
        N = (int)A.size();
        table.assign(MAX_LOG, vector<int>(N));

        // 2^0 回後（1回遷移）
        for (int i = 0; i < N; i++)
        {
            table[0][i] = A[i];
        }

        // 2^k 回後
        for (int k = 1; k < MAX_LOG; k++)
        {
            for (int i = 0; i < N; i++)
            {
                table[k][i] = table[k - 1][table[k - 1][i]];
            }
        }
    }

    // ===== クエリ：pos から K 回遷移した先 =====
    int jump(int pos, long long K)
    {
        int cur = pos;
        for (int k = 0; k < MAX_LOG; k++)
        {
            if ((K >> k) & 1LL)
            {
                cur = table[k][cur];
            }
        }
        return cur;
    }
};

int main()
{
    int N, Q;
    cin >> N >> Q;
    vi A(N + 1);
    vll X(Q + 1), Y(Q + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> A[i];
    }
    Doubling A_doubling(A);
    for (int j = 1; j <= Q; j++)
    {
        cin >> X[j] >> Y[j];
        cout << A_doubling.jump(X[j], Y[j]) << endl;
    }
}

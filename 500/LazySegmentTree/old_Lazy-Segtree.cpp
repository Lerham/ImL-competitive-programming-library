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

const int MAX_N = 1e5 + 9;
const int MAX_Q = 1e5 + 9;
const int SEG_SIZE = 4 * MAX_N;

int N, Q;
ll A[MAX_N];
char T[MAX_Q];
int L[MAX_Q], R[MAX_Q];
ll X[MAX_Q];

// セグメント木
// lazyseg_uni[k] :
//   頂点 k に対して、その区間全体に一様に加算される値
// lazyseg_nonuni_sum[k] :
//   頂点 k に対して、その区間に対する部分加算ぶんの総和
ll lazyseg_uni[SEG_SIZE], lazyseg_nonuni_sum[SEG_SIZE];

// 区間 [a, b) に値 x を加算する関数
// k は現在の node 番号で、区間 [l, r) を担当する
// 根は [0, N) を表す
void add(int a, int b, ll x, int k, int l, int r)
{
    if (a <= l && r <= b)
    {
        // [l, r) が完全に含まれるとき
        lazyseg_uni[k] += x;
    }
    else if (l < b && a < r)
    {
        // 一部だけ重なるときは、この節点には増加した総量を記録し、子へ再帰する
        int mid = (l + r) / 2;
        lazyseg_nonuni_sum[k] += 1LL * (min(b, r) - max(a, l)) * x;
        add(a, b, x, 2 * k + 1, l, mid);
        add(a, b, x, 2 * k + 2, mid, r);
    }
}

// 区間 [a, b) の総和を求める関数
// k は現在の node 番号で、区間 [l, r) を担当する
ll sum(int a, int b, int k, int l, int r)
{
    if (b <= l || r <= a)
    {
        // 交わらない
        return 0;
    }
    if (a <= l && r <= b)
    {
        // 完全に含まれる
        return lazyseg_nonuni_sum[k] + lazyseg_uni[k] * (r - l);
    }
    else
    {
        // 一部だけ重なる
        int mid = (l + r) / 2;
        ll result = 1LL * (min(b, r) - max(a, l)) * lazyseg_uni[k];
        result += sum(a, b, 2 * k + 1, l, mid);
        result += sum(a, b, 2 * k + 2, mid, r);
        return result;
    }
}

int main()
{
    cin >> N >> Q;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        add(i, i + 1, A[i], 0, 0, N);
    }
    for (int i = 0; i < Q; i++)
    {
        cin >> T[i];
        if (T[i] == '1')
        {
            cin >> L[i] >> R[i] >> X[i];
            add(L[i], R[i], X[i], 0, 0, N);
        }
        else if (T[i] == '2')
        {
            cin >> L[i] >> R[i];
            cout << sum(L[i], R[i], 0, 0, N) << endl;
        }
    }
}

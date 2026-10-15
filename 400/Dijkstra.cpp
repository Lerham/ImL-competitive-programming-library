#include <bits/stdc++.h>
#include <set>
#define rep(i, n) for (int i = 0; i < N; i++)
using namespace std;

using ll = long long;

// ======== dikstra 法 ========
vector<ll> dijkstra(
    const vector<vector<pair<int, ll>>>& G,
    int start
)
{
    int N = G.size() - 1;

    // pqの小さい順に取る優先度つきキュー  {cost, 頂点番号}
    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > Q;

    vector<bool> kakutei(N + 1, false); //頂点の確定kakutei[i]
    vector<ll> cur(N + 1, -1); //現在の暫定的最短距離cur[i]

    cur[start] = 0;
    Q.push({0, start});

    while (Q.empty() == false)
    {
        // ========== 侵入時の処理 ==========
        ll current_cost = Q.top().first;
        int pos = Q.top().second;
        Q.pop();

        if (kakutei[pos] == true)
        {
            continue;
        }

        kakutei[pos] = true;
        int x = G[pos].size();

        for (int i = 0; i < x; i++)
        {
            int nex = G[pos][i].first;
            ll cost = G[pos][i].second;

            if (kakutei[nex] == true)
            {
                continue;
            }

            // 更新するための条件は, 未探索(cost = -1) であるか, それよりも小さいcostであるか
            if (cur[nex] == -1 || cur[nex] > cur[pos] + cost)
            {
                cur[nex] = cur[pos] + cost;
                Q.push({cur[nex], nex});
                //    cout << nex << endl;
            }
        }// i

        // ========= 退出時の処理 ==========

    }//while

    return cur;
}

int main()
{
    int N, M;
    cin >> N >> M;

    vector<int> A(M + 1), B(M + 1);
    vector<ll> C(M + 1);

    // グラフを定義
    vector<vector<pair<int, ll>>> G(N + 1); // first:頂点番号, second:cost
    for (int i = 1; i <= M; i++)
    {
        cin >> A[i] >> B[i] >> C[i]; // 辺の情報とコストの情報
        G[A[i]].push_back({B[i], C[i]});
        G[B[i]].push_back({A[i], C[i]});
    }

    vector<ll> cur = dijkstra(G, 1);

    for (int i = 1; i <= N; i++)
    {
        cout << cur[i] << endl;
    }
}
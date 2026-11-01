#include <bits/stdc++.h>
using namespace std;

// 1-indexed / 重みなしの木専用（距離 = 通る辺の本数）
struct TreeDiameterResult {
    int length;         // 直径の長さ（辺の本数）
    int u, v;           // 直径の両端点
    vector<int> path;   // u -> v の頂点列
};

struct TreeBFSResult {
    int farthest;        // 始点から最も遠い頂点
    vector<int> dist;   // 始点からの距離
    vector<int> parent; // 探索でたどった親
};

// start から BFS（幅優先探索）して最遠点・距離・親を求める
TreeBFSResult tree_bfs(const vector<vector<int>>& G, int start) {
    int N = (int)G.size() - 1;
    vector<int> dist(N + 1, -1), parent(N + 1, -1);
    queue<int> que;
    dist[start] = 0;
    que.push(start);
    int farthest = start;

    while (!que.empty()) {
        int v = que.front();
        que.pop();
        if (dist[v] > dist[farthest]) farthest = v;

        for (int to : G[v]) {
            if (dist[to] != -1) continue;
            dist[to] = dist[v] + 1;
            parent[to] = v;
            que.push(to);
        }
    }
    return {farthest, move(dist), move(parent)};
}

// 木の直径を BFS 2 回で求める。時間 O(N)、追加メモリ O(N)。
TreeDiameterResult tree_diameter(const vector<vector<int>>& G) {
    int N = (int)G.size() - 1;
    if (N <= 0) return {0, 0, 0, {}};

    int u = tree_bfs(G, 1).farthest;
    auto second = tree_bfs(G, u);
    int v = second.farthest;

    vector<int> path;
    for (int x = v; x != -1; x = second.parent[x]) {
        path.push_back(x);
    }
    reverse(path.begin(), path.end());
    return {second.dist[v], u, v, path};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> G(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    auto result = tree_diameter(G);
    cout << result.length << '\n';
    // 頂点数を求める問題なら result.length + 1 を出力する。
    // 端点: result.u, result.v / 経路: result.path
}

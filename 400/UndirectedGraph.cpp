// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/400/UndirectedGraph.cpp
#include <bits/stdc++.h>
using namespace std;


// ============================================================
// 重みなし無向グラフ
// ============================================================

struct UndirectedGraph {
    // 隣接リストに保存する辺
    struct Edge {
        int to; // 行き先の頂点
        int id; // 辺番号
    };

    // BFSの結果
    struct BFSResult {
        vector<int> dist;    // 始点からの最短距離。到達不能なら -1
        vector<int> parent;  // BFS木における親。始点や到達不能なら -1
        vector<int> order;   // BFSで頂点を取り出した順番

        // BFSの始点から target までの最短経路を復元する
        //
        // 例:
        // 始点1から target=5 への経路が
        // 1 -> 3 -> 4 -> 5
        // なら {1, 3, 4, 5} を返す。
        //
        // targetに到達できない場合は空vectorを返す。
        vector<int> path_to(int target) const {
            if (target < 0 || target >= (int)dist.size()) {
                return {};
            }

            if (dist[target] == -1) {
                return {};
            }

            vector<int> path;

            for (int v = target; v != -1; v = parent[v]) {
                path.push_back(v);
            }

            reverse(path.begin(), path.end());
            return path;
        }
    };

    // DFSの結果
    struct DFSResult {
        vector<bool> visited; // 始点から到達できたか
        vector<int> parent;   // DFS木における親
        vector<int> order;    // 初めて訪問した順番
    };

    // 二部グラフ判定の結果
    struct BipartiteResult {
        bool is_bipartite;

        // color[v] は 0 または 1。
        // 連結成分ごとに適当に2色で塗る。
        vector<int> color;
    };

    int n;                         // 頂点数
    int edge_count;                // 辺数
    vector<vector<Edge>> graph;    // 隣接リスト

    // 頂点番号は 1 ～ n を使う。
    explicit UndirectedGraph(int n)
        : n(n), edge_count(0), graph(n + 1) {}


    // --------------------------------------------------------
    // 辺を追加する
    // --------------------------------------------------------

    void add_edge(int u, int v) {
        // 同じ辺番号で、両方向の辺を登録する。
        //
        // u -- v は隣接リスト上では
        //
        // u -> v
        // v -> u
        //
        // の2本として保存される。
        graph[u].push_back({v, edge_count});
        graph[v].push_back({u, edge_count});

        edge_count++;
    }


    // --------------------------------------------------------
    // 頂点の次数
    // --------------------------------------------------------

    int degree(int v) const {
        return (int)graph[v].size();
    }

    vector<int> degrees() const {
        vector<int> result(n + 1);

        for (int v = 1; v <= n; v++) {
            result[v] = degree(v);
        }

        return result;
    }


    // --------------------------------------------------------
    // BFS
    // --------------------------------------------------------

    BFSResult bfs(int start) const {
        vector<int> dist(n + 1, -1);
        vector<int> parent(n + 1, -1);
        vector<int> order;

        queue<int> que;

        dist[start] = 0;
        que.push(start);

        while (!que.empty()) {
            int v = que.front();
            que.pop();

            order.push_back(v);

            for (const Edge& edge : graph[v]) {
                int next = edge.to;

                // すでに訪問済みなら何もしない。
                if (dist[next] != -1) {
                    continue;
                }

                dist[next] = dist[v] + 1;
                parent[next] = v;
                que.push(next);
            }
        }

        return {dist, parent, order};
    }


    // startからgoalまでの最短経路を返す。
    //
    // 重みなしグラフなので、BFSによる経路が最短になる。
    vector<int> shortest_path(int start, int goal) const {
        BFSResult result = bfs(start);
        return result.path_to(goal);
    }


    // --------------------------------------------------------
    // DFS
    // --------------------------------------------------------

    DFSResult dfs(int start) const {
        vector<bool> visited(n + 1, false);
        vector<int> parent(n + 1, -1);
        vector<int> order;

        // 再帰ではなくstackを使う。
        // 頂点数が大きい場合のスタックオーバーフローを避けやすい。
        stack<int> st;

        visited[start] = true;
        st.push(start);

        while (!st.empty()) {
            int v = st.top();
            st.pop();

            order.push_back(v);

            // 後ろから追加すると、隣接リストの先頭側を
            // 比較的先に訪問できる。
            for (int i = (int)graph[v].size() - 1; i >= 0; i--) {
                int next = graph[v][i].to;

                if (visited[next]) {
                    continue;
                }

                visited[next] = true;
                parent[next] = v;
                st.push(next);
            }
        }

        return {visited, parent, order};
    }


    // --------------------------------------------------------
    // 連結成分
    // --------------------------------------------------------

    // component[v] =
    // 頂点vが何番目の連結成分に属するか。
    //
    // 連結成分番号は 0, 1, 2, ... とする。
    vector<int> connected_components() const {
        vector<int> component(n + 1, -1);

        int component_id = 0;

        for (int start = 1; start <= n; start++) {
            if (component[start] != -1) {
                continue;
            }

            queue<int> que;
            component[start] = component_id;
            que.push(start);

            while (!que.empty()) {
                int v = que.front();
                que.pop();

                for (const Edge& edge : graph[v]) {
                    int next = edge.to;

                    if (component[next] != -1) {
                        continue;
                    }

                    component[next] = component_id;
                    que.push(next);
                }
            }

            component_id++;
        }

        return component;
    }


    int connected_components_count() const {
        vector<int> component = connected_components();

        int maximum_id = -1;

        for (int v = 1; v <= n; v++) {
            maximum_id = max(maximum_id, component[v]);
        }

        return maximum_id + 1;
    }


    bool is_connected() const {
        if (n == 0) {
            return true;
        }

        BFSResult result = bfs(1);

        for (int v = 1; v <= n; v++) {
            if (result.dist[v] == -1) {
                return false;
            }
        }

        return true;
    }


    // --------------------------------------------------------
    // 二部グラフ判定
    // --------------------------------------------------------

    BipartiteResult bipartite_check() const {
        vector<int> color(n + 1, -1);

        // 非連結グラフにも対応するため、
        // 全頂点を始点候補として調べる。
        for (int start = 1; start <= n; start++) {
            if (color[start] != -1) {
                continue;
            }

            queue<int> que;

            color[start] = 0;
            que.push(start);

            while (!que.empty()) {
                int v = que.front();
                que.pop();

                for (const Edge& edge : graph[v]) {
                    int next = edge.to;

                    if (color[next] == -1) {
                        // 隣接頂点を反対の色に塗る。
                        color[next] = color[v] ^ 1;
                        que.push(next);
                    }
                    else if (color[next] == color[v]) {
                        // 同じ色同士が隣接したので二部グラフではない。
                        return {false, color};
                    }
                }
            }
        }

        return {true, color};
    }


    bool is_bipartite() const {
        return bipartite_check().is_bipartite;
    }


    // --------------------------------------------------------
    // 閉路を1つ探す
    // --------------------------------------------------------

    // 閉路が存在する場合、
    //
    // 例:
    // 2 -> 4 -> 7 -> 2
    //
    // に対して
    //
    // {2, 4, 7, 2}
    //
    // のように、最初と最後を同じ頂点にしたvectorを返す。
    //
    // 閉路がなければ空vectorを返す。
    //
    // 辺番号を使って「今通ってきた辺だけ」を除外するので、
    // 多重辺にも対応できる。
    vector<int> find_cycle() const {
        // state:
        // 0 = 未訪問
        // 1 = 現在DFS中
        // 2 = DFS完了
        vector<int> state(n + 1, 0);

        vector<int> parent_vertex(n + 1, -1);
        vector<int> parent_edge(n + 1, -1);

        vector<int> cycle;

        auto dfs_cycle = [&](auto&& self, int v, int incoming_edge) -> bool {
            state[v] = 1;

            for (const Edge& edge : graph[v]) {
                int next = edge.to;

                // 今通ってきた同じ辺を逆向きに見る操作は無視する。
                if (edge.id == incoming_edge) {
                    continue;
                }

                if (state[next] == 0) {
                    parent_vertex[next] = v;
                    parent_edge[next] = edge.id;

                    if (self(self, next, edge.id)) {
                        return true;
                    }
                }
                else if (state[next] == 1) {
                    // 現在DFS中の祖先へ戻る辺を発見した。
                    // ここから閉路を復元する。

                    cycle.push_back(next);

                    int current = v;

                    while (current != next) {
                        cycle.push_back(current);
                        current = parent_vertex[current];
                    }

                    cycle.push_back(next);

                    return true;
                }
            }

            state[v] = 2;
            return false;
        };

        for (int start = 1; start <= n; start++) {
            if (state[start] != 0) {
                continue;
            }

            if (dfs_cycle(dfs_cycle, start, -1)) {
                return cycle;
            }
        }

        return {};
    }


    bool has_cycle() const {
        return !find_cycle().empty();
    }
};


// ============================================================
// 木
// ============================================================
//
// TreeはUndirectedGraphを継承する。
//
// そのため、Treeでも以下をそのまま使える:
//
// add_edge
// bfs
// dfs
// shortest_path
// degree
// is_connected
// など
//
// Tree側には「入力が木であるときだけ正しい処理」を追加する。
// ============================================================

struct Tree : UndirectedGraph {
    // 根付き木として見たときの情報
    struct RootedTreeInfo {
        int root;

        vector<int> parent;
        vector<int> depth;
        vector<int> subtree_size;
        vector<int> order;
    };

    // 木の直径の情報
    struct DiameterResult {
        int length;       // 直径の辺数
        int start;        // 直径の一方の端点
        int goal;         // 直径のもう一方の端点
        vector<int> path; // 直径をなす頂点列
    };

    explicit Tree(int n)
        : UndirectedGraph(n) {}


    // --------------------------------------------------------
    // 本当に木になっているか確認する
    // --------------------------------------------------------

    bool is_tree() const {
        // 頂点数nの無向グラフが木である条件:
        //
        // 1. 連結
        // 2. 辺数が n - 1
        //
        // の両方を満たすこと。
        if (n == 0) {
            return true;
        }

        return edge_count == n - 1 && is_connected();
    }


    // --------------------------------------------------------
    // 根付き木の情報を作る
    // --------------------------------------------------------

    RootedTreeInfo rooted_info(int root = 1) const {
        vector<int> parent(n + 1, -1);
        vector<int> depth(n + 1, -1);
        vector<int> subtree_size(n + 1, 1);
        vector<int> order;

        stack<int> st;

        depth[root] = 0;
        st.push(root);

        while (!st.empty()) {
            int v = st.top();
            st.pop();

            order.push_back(v);

            for (const Edge& edge : graph[v]) {
                int next = edge.to;

                // 親の方向には戻らない。
                if (next == parent[v]) {
                    continue;
                }

                // 木であるなら本来これだけでもよいが、
                // 誤って木でない入力を渡した場合の無限巡回を防ぐ。
                if (depth[next] != -1) {
                    continue;
                }

                parent[next] = v;
                depth[next] = depth[v] + 1;
                st.push(next);
            }
        }

        // DFS順を逆から見る。
        //
        // 子のsubtree_sizeを親に加えることで、
        // 各頂点を根とする部分木のサイズが求まる。
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int v = order[i];

            if (parent[v] != -1) {
                subtree_size[parent[v]] += subtree_size[v];
            }
        }

        return {
            root,
            parent,
            depth,
            subtree_size,
            order
        };
    }


    vector<int> parents(int root = 1) const {
        return rooted_info(root).parent;
    }


    vector<int> depths(int root = 1) const {
        return rooted_info(root).depth;
    }


    vector<int> subtree_sizes(int root = 1) const {
        return rooted_info(root).subtree_size;
    }


    // --------------------------------------------------------
    // 木上のuからvまでの経路
    // --------------------------------------------------------

    vector<int> path(int u, int v) const {
        // 木ではuからvへの単純路は一意。
        //
        // bfs(u)から親を復元すれば、その一意な経路が得られる。
        return shortest_path(u, v);
    }


    // --------------------------------------------------------
    // 木の直径
    // --------------------------------------------------------

    DiameterResult diameter() const {
        if (n == 0) {
            return {0, -1, -1, {}};
        }

        // まず適当な頂点1から最も遠い頂点を探す。
        BFSResult first_bfs = bfs(1);

        int start = 1;

        for (int v = 1; v <= n; v++) {
            if (first_bfs.dist[v] > first_bfs.dist[start]) {
                start = v;
            }
        }

        // startから最も遠い頂点goalを探す。
        // startとgoalが木の直径の端点になる。
        BFSResult second_bfs = bfs(start);

        int goal = start;

        for (int v = 1; v <= n; v++) {
            if (second_bfs.dist[v] > second_bfs.dist[goal]) {
                goal = v;
            }
        }

        vector<int> diameter_path = second_bfs.path_to(goal);

        return {
            second_bfs.dist[goal],
            start,
            goal,
            diameter_path
        };
    }


    // --------------------------------------------------------
    // 木の中心
    // --------------------------------------------------------

    // 木の中心:
    // 全頂点への最大距離を最小にする頂点。
    //
    // 直径の中央にある。
    //
    // 直径の頂点数が奇数なら中心は1個。
    // 直径の頂点数が偶数なら中心は2個。
    vector<int> centers() const {
        DiameterResult result = diameter();
        const vector<int>& diameter_path = result.path;

        int size = (int)diameter_path.size();

        if (size == 0) {
            return {};
        }

        if (size % 2 == 1) {
            return {diameter_path[size / 2]};
        }

        return {
            diameter_path[size / 2 - 1],
            diameter_path[size / 2]
        };
    }


    // --------------------------------------------------------
    // 木の重心
    // --------------------------------------------------------

    // 木の重心:
    // その頂点を削除したとき、
    // 残る各連結成分の頂点数がすべて n/2 以下になる頂点。
    //
    // 木の重心は1個または2個存在する。
    vector<int> centroids() const {
        if (n == 0) {
            return {};
        }

        RootedTreeInfo info = rooted_info(1);

        vector<int> result;

        for (int v = 1; v <= n; v++) {
            // vの親側にある頂点数
            int largest_component = n - info.subtree_size[v];

            // vの子側にある各部分木のサイズを調べる。
            for (const Edge& edge : graph[v]) {
                int next = edge.to;

                if (info.parent[next] == v) {
                    largest_component =
                        max(largest_component, info.subtree_size[next]);
                }
            }

            if (largest_component <= n / 2) {
                result.push_back(v);
            }
        }

        return result;
    }


    // --------------------------------------------------------
    // 葉
    // --------------------------------------------------------

    vector<int> leaves() const {
        vector<int> result;

        // 頂点が1個だけの木では、その頂点を葉とする。
        if (n == 1) {
            return {1};
        }

        for (int v = 1; v <= n; v++) {
            if (degree(v) == 1) {
                result.push_back(v);
            }
        }

        return result;
    }
};

int main() {
    int N;
    cin >> N;

    Tree tree(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        tree.add_edge(u, v);
    }

    // 1から各頂点までの距離
    auto bfs_result = tree.bfs(1);

    for (int v = 1; v <= N; v++) {
        cout << "dist["
             << v
             << "] = "
             << bfs_result.dist[v]
             << '\n';
    }

    // 根を1としたときの情報
    auto rooted = tree.rooted_info(1);

    for (int v = 1; v <= N; v++) {
        cout << "vertex = " << v
             << ", parent = " << rooted.parent[v]
             << ", depth = " << rooted.depth[v]
             << ", subtree_size = " << rooted.subtree_size[v]
             << '\n';
    }

    // 木の直径
    auto diameter = tree.diameter();

    cout << "diameter length = "
         << diameter.length
         << '\n';

    cout << "diameter path: ";

    for (int v : diameter.path) {
        cout << v << ' ';
    }

    cout << '\n';
}
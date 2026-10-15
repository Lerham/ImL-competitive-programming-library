int N, M;
vector<bool> visited(200009);
vector<vector<int>> G(200009);  // 隣接リスト

// DFS
void dfs(int pos, vector<vector<int>>& G,
         vector<bool>& visited) {  // 今いるpos(i番)から深さ優先探索を行う)
    visited[pos] = true;           // 1以上の数 => 着色
    int x = G[pos].size();
    //============侵入の処理=============

    //==================================
    for (int j = 0; j < x; j++) {
        int nex = G[pos][j];          // posに隣接する頂点.
        if (visited[nex] == false) {  // 未探索のとき
            dfs(nex, G, visited);     // nexに侵入.

        }  // if visited false
    }  // for j

    //============退出の処理=============

    //==================================
}

// 探索順番の数を付与するDFS
void dfs(int pos, int i) {  // 今いるpos(i番)から深さ優先探索を行う
    visited[pos] = i;       // 1以上の数 => 着色
    int x = G[pos].size();
    for (int j = 0; j < x; j++) {
        int nex = G[pos][j];  // 現在位置に隣接するやつを順に見る.

        if (visited[nex] == 0) {  // まだ着色されてない

            dfs(nex, i + 1);  // 白ならnexに行く.
            // mymap[nex] = pos;
        }
    }
}
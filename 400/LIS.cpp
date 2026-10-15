#include <bits/stdc++.h>
#include <set>
#include <queue>
using namespace std;


// 小さい変数:
// 大きい変数:
int main() {

int N, X[100009], Y[100009];

//入力
cin >> N;
vector<pair<int, int>> vec(100009);
for (int i=1; i<=N; i++){
cin >> X[i] >> Y[i];
vec[i] = {X[i], -Y[i]};
}

sort(vec.begin() + 1, vec.begin() + 1 + N);
// X[1] < X[2] < ... にできた. あとはYについてLISを解けばよいのでは。

for (int i=1; i<=N; i++){
vec[i].second = -vec[i].second;
}


int LEN = 0, L[100009], dp[100009], A[100009];
for (int i=1; i<=N; i++){
  A[i] = vec[i].second;
}
L[0] = -1;

// dp[i] = 末尾がA[i]であるような部分増加列の長さの最大値
// L[x] = dp[i] = xであるようなiに対するA[i]の最小値（for iをやりつつ暫定的に更新していく）
// LENは配列の長さ

//LISを解く. 
for (int i=1; i<=N; i++){
  int pos; //A[i] <= L[pos] であるような最小のpos (1,...,LEN)
  
  // 二分探索
  int ac = 0;
  int wa = LEN+1;
  while (wa - ac > 1){
    int wj = (ac + wa)/2;
    if (A[i] > L[wj]){
      ac = wj;
    }
    else {
      wa = wj;
    }
  }
  pos = ac;
  dp[i] = pos + 1;
  L[dp[i]] = A[i]; // 本当はminと考えるべきだけどA[i]の時点で自動的にminになってる. 
  if (dp[i] > LEN){
  LEN++;  
  }
  
  
  
}

cout << LEN << endl;

//int ans;
//cout << ans << endl;

}
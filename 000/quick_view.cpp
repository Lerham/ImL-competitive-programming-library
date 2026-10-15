// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/000/quick_view.cpp
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
//MOD
const ll mod = 998244353; 
using mint = atcoder::modint998244353;

void YesNo(bool ok) {
    cout << (ok ? "Yes" : "No") << '\n';
}


int main() {

ll N; cin >> N;
vector<ll> A(N+1);
for(int i=1; i<=N; i++) { 
    cin >> A[i];
}

//====Grid World====
int H,W;
cin >> H >> W;
vector<string> S(1009); //文字列の列
for (int i=1; i<=H; i++){
	cin >> S[i];
	S[i] = '#' + S[i] + "#"; //補正(W+2文字)
}

//番兵
for (int i=0; i<=W+1; i++){
	S[0] = "#" + S[0];
	S[H+1] = "#" + S[H];
}
//===================


string S; cin >> S;


//出力関連
cout << fixed << setprecision(12) << ans << endl; //小数点以下12桁まで出力

}

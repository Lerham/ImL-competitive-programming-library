#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;

ll gcd(ll A, ll B)
{
    if (B == 0){
        return A;
    }
    return gcd(B, A % B);
}

void large_lcm(ll A, ll B)
{
    //典型90のLarge LCM問題
    //1 <= A, B <= 10^18 で LCM(A,B)を求める. 
    //A*Bが10^18を超える場合は"Large"と出力する.

    ll g = gcd(A, B); 

    ll A_red = A / g;
    ll B_red = B / g;
    ll q_1 = (1000000000000000000LL)/(B_red*g);
    ll lcm;
    bool large = false;
    if (A_red > q_1){  large = true;}
    else{
      lcm = A_red*B_red*g;
    }
    

    if (large){
        cout << "Large" << endl;
    }
    else{
        cout << lcm << endl;
    }
}

int main()
{


}

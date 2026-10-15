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

void YesNo(bool ok) { cout << (ok ? "Yes" : "No") << '\n'; }

using ll = long long;

// 素数判定：O(sqrt(n))
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    // p * p <= n だとオーバーフローしうるため、p <= n / p
    for (ll p = 3; p <= n / p; p += 2) {
        if (n % p == 0) return false;
    }

    return true;
}

// n 以下の素数を昇順で返す：エラトステネスの篩
vector<ll> prime_generator(ll n) {
    if (n < 2) return {};

    // vectorの添字・メモリ確保が不可能な値を弾く
    if (static_cast<unsigned long long>(n) >=
        static_cast<unsigned long long>(vector<bool>().max_size())) {
        throw length_error("n is too large for prime_generator");
    }

    vector<bool> is_prime_table(static_cast<size_t>(n) + 1, true);
    is_prime_table[0] = false;
    is_prime_table[1] = false;

    for (ll p = 2; p <= n / p; p++) {
        if (!is_prime_table[static_cast<size_t>(p)]) continue;

        // p*p は p <= n/p が成立しているのでオーバーフローしない
        for (ll x = p * p; x <= n;) {
            is_prime_table[static_cast<size_t>(x)] = false;

            // x += p のオーバーフロー防止
            if (x > n - p) break;
            x += p;
        }
    }

    vector<ll> primes;
    for (ll x = 2; x <= n; x++) {
        if (is_prime_table[static_cast<size_t>(x)]) {
            primes.push_back(x);
        }
    }

    return primes;
}

int main() {
    // int N; cin >> N;

    // string S; cin >> S;
}

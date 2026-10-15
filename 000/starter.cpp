// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/000/starter.cpp
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
// const ll mod = 1000000007;
// using mint = atcoder::modint1000000007;

#define rep(i, n) for (ll i = 1; i <= n; i++)
#define reps(i, l, r) for (ll i = (l); i <= (r); i++)
#define rrep(i, n) for (ll i = (n); i >= 1; i--)

// Debug用
namespace debug_detail {
template <class T, class = void>
struct is_iterable : false_type {};
template <class T>
struct is_iterable<T,
                   void_t<decltype(begin(declval<const T&>())), decltype(end(declval<const T&>()))>>
    : true_type {};
template <class T>
struct is_pair : false_type {};
template <class A, class B>
struct is_pair<pair<A, B>> : true_type {};
template <class T, class = void>
struct is_tuple : false_type {};
template <class T>
struct is_tuple<T, void_t<decltype(tuple_size<T>::value)>> : true_type {};

template <class T>
string repr(const T& value);
template <class Tuple, size_t... I>
string repr_tuple(const Tuple& value, index_sequence<I...>) {
    string result = "(";
    ((result += (I == 0 ? "" : ", ") + repr(get<I>(value))), ...);
    return result + ")";
}
template <class T>
string repr(const T& value) {
    using U = decay_t<T>;
    if constexpr (is_same_v<U, string>)
        return '"' + value + '"';
    else if constexpr (is_same_v<U, char>)
        return string("'") + value + "'";
    else if constexpr (is_pair<U>::value)
        return "(" + repr(value.first) + ", " + repr(value.second) + ")";
    else if constexpr (is_tuple<U>::value)
        return repr_tuple(value, make_index_sequence<tuple_size<U>::value>{});
    else if constexpr (is_iterable<U>::value) {
        string result = "[";
        bool first = true;
        for (const auto& item : value) {
            if (!first) result += ", ";
            result += repr(item);
            first = false;
        }
        return result + "]";
    } else {
        ostringstream oss;
        oss << value;
        return oss.str();
    }
}
inline vector<string> split_names(string_view names) {
    vector<string> result;
    int depth = 0;
    size_t left = 0;
    for (size_t i = 0; i < names.size(); ++i) {
        const char ch = names[i];
        if (ch == '(' || ch == '[' || ch == '{' || ch == '<') ++depth;
        if (ch == ')' || ch == ']' || ch == '}' || ch == '>') --depth;
        if (ch == ',' && depth == 0) {
            result.emplace_back(names.substr(left, i - left));
            left = i + 1;
        }
    }
    result.emplace_back(names.substr(left));
    for (string& name : result) {
        const size_t first = name.find_first_not_of(" \t");
        const size_t last = name.find_last_not_of(" \t");
        name = first == string::npos ? "" : name.substr(first, last - first + 1);
    }
    return result;
}
}  // namespace debug_detail（表示用の整形処理）

vector<string> debug_log;
template <class... Ts>
void append_debug_log(const char* file, int line, const char* function, string_view names,
                      const Ts&... values) {
    const vector<string> labels = debug_detail::split_names(names);
    const vector<string> rendered{debug_detail::repr(values)...};
    string filename(file);
    const size_t slash = filename.find_last_of("\\\\/");
    if (slash != string::npos) filename = filename.substr(slash + 1);
    ostringstream oss;
    oss << '[' << filename << ":L" << line << ' ' << function << "] ";
    for (size_t i = 0; i < rendered.size(); ++i) {
        if (i != 0) oss << ", ";
        oss << (i < labels.size() ? labels[i] : "arg" + to_string(i)) << " = " << rendered[i];
    }
    debug_log.push_back(oss.str());
}

inline void append_debug_mark(const char* file, int line, const char* function,
                              string_view message) {
    string filename(file);
    const size_t slash = filename.find_last_of("\\\\/");
    if (slash != string::npos) filename = filename.substr(slash + 1);
    ostringstream oss;
    oss << '[' << filename << ":L" << line << ' ' << function << "] ---- " << message << " ----";
    debug_log.push_back(oss.str());
}

#define debug(...)                                                                  \
    do {                                                                            \
        if constexpr (do_debug) append_debug_log(__FILE__, __LINE__, __func__,     \
                                                  #__VA_ARGS__, __VA_ARGS__);       \
    } while (false)
#define debug_mark(message)                                                         \
    do {                                                                            \
        if constexpr (do_debug) append_debug_mark(__FILE__, __LINE__, __func__, message); \
    } while (false)
// 使用例: debug(i, x, dp);  // [starter.cpp:L123 solve] i = 3, x = 7, dp = [0, 4, 9]
//         debug(mp, make_pair(a, b), tie(l, r));
//         debug_mark("クエリ読込完了");

constexpr bool do_debug = true;  // true にすると標準出力へ表示され、提出時は WA になる

void print_debug_log() {
    if (!do_debug || debug_log.empty()) return;
    cout << "\n========== DEBUG ==========\n";
    for (const string& s : debug_log) {
        cout << s << '\n';
    }
    cout << "===========================\n";
}
void printyn(bool ok) { cout << (ok ? "Yes" : "No") << endl; }

ll N, M, Q, T;
vll A(500009);
string S;
int H, W;
vector<string> grid(300009);

int main() {
    // mainの最後で一括表示
    print_debug_log();
}

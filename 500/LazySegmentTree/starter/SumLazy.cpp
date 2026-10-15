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

constexpr bool do_debug = false;  // true にすると標準出力へ表示され、提出時は WA になる

void print_debug_log() {
    if (!do_debug || debug_log.empty()) return;
    cout << "\n========== DEBUG ==========\n";
    for (const string& s : debug_log) {
        cout << s << '\n';
    }
    cout << "===========================\n";
}
void printyn(bool ok) { cout << (ok ? "Yes" : "No") << endl; }


// 区間加算・区間和用のStateと遅延タグ.
struct RangeAddLazy {
    long long add;

    static RangeAddLazy e() { return {0}; }
    static bool is_id(const RangeAddLazy& action) { return action.add == 0; }
    static RangeAddLazy compose(const RangeAddLazy& old_action, const RangeAddLazy& new_action) {
        return {old_action.add + new_action.add};
    }
};

struct RangeAddSumState {
    long long sum;

    static RangeAddSumState e() { return {0}; }
    static RangeAddSumState make_leaf(long long x, int array_id) { return {x}; }
    static RangeAddSumState op(const RangeAddSumState& left, const RangeAddSumState& right) {
        return {left.sum + right.sum};
    }
    static RangeAddSumState apply(const RangeAddSumState& state, const RangeAddLazy& action, int length) {
        return {state.sum + action.add * length};
    }
};

// State は次を持つ.
//   static State e();
//   static State op(const State& left, const State& right);
//   static State apply(const State& state, const Lazy& action, int length);
//
// Lazy は次を持つ.
//   static Lazy e();
//   static bool is_id(const Lazy& action);
//   static Lazy compose(const Lazy& old_action, const Lazy& new_action);
// compose(old, new)は「oldを適用した後にnewを適用する」タグを返す.
//
// 使い方 (配列は1-indexed、区間は閉区間[l,r]).
//   LazySegmentTree<RangeAddSumState, RangeAddLazy> seg;
//   seg.init(N);
//   for (int i = 1; i <= N; i++) {
//       seg.update(i, RangeAddSumState::make_leaf(A[i], i));
//   }
//   seg.range_apply(L, R, {x});  // 閉区間[L,R]へxを加算
//   auto ans = seg.query(L, R);
template <class State, class Lazy>
class LazySegmentTree {
   public:
    vector<State> dat;
    vector<Lazy> lazy;
    int siz = 1;  // sizは葉の個数となる2冪.

    State op(const State& left, const State& right) {
        return State::op(left, right);
    }

    State e() { return State::e(); }

    // 要素datと遅延タグの初期化.
    void init(int N) {
        siz = 1;
        while (siz < N) {
            siz *= 2;  // sizはセグ木下部の要素数の上界となる2冪.
        }
        dat.assign(2 * siz, e());
        lazy.assign(2 * siz, Lazy::e());
    }

    //(1) array_idの要素をvalueに代入し, その経路の遅延タグを伝播して更新せよ.
    void update(int array_id, const State& value) {
        update(array_id, value, 1, siz, 1);
    }

    // 閉区間[l,r]にactionを適用する.
    void range_apply(int l, int r, const Lazy& action) {
        range_apply(l, r, action, 1, siz, 1);
    }

    // 閉区間[l,r]におけるStateを返す.
    State query(int l, int r) { return query(l, r, 1, siz, 1); }

   private:
    // cell_idの担当閉区間[a,b]全体にactionを適用する.
    void apply_to(int cell_id, int a, int b, const Lazy& action) {
        dat[cell_id] = State::apply(dat[cell_id], action, b - a + 1);
        lazy[cell_id] = Lazy::compose(lazy[cell_id], action);
    }

    // cell_idに溜まった遅延タグを子へ下ろす.
    void push(int cell_id, int a, int b) {
        if (a == b || Lazy::is_id(lazy[cell_id])) return;
        int m = (a + b) / 2;
        apply_to(cell_id * 2, a, m, lazy[cell_id]);
        apply_to(cell_id * 2 + 1, m + 1, b, lazy[cell_id]);
        lazy[cell_id] = Lazy::e();
    }

    void pull(int cell_id) {
        dat[cell_id] = op(dat[cell_id * 2], dat[cell_id * 2 + 1]);
    }

    void update(int array_id, const State& value, int a, int b, int cell_id) {
        if (a == b) {
            dat[cell_id] = value;
            lazy[cell_id] = Lazy::e();
            return;
        }
        push(cell_id, a, b);
        int m = (a + b) / 2;
        if (array_id <= m) {
            update(array_id, value, a, m, cell_id * 2);
        } else {
            update(array_id, value, m + 1, b, cell_id * 2 + 1);
        }
        pull(cell_id);
    }

    void range_apply(int l, int r, const Lazy& action, int a, int b, int cell_id) {
        if (r < a || b < l) return;
        if (l <= a && b <= r) {
            apply_to(cell_id, a, b, action);
            return;
        }
        push(cell_id, a, b);
        int m = (a + b) / 2;
        range_apply(l, r, action, a, m, cell_id * 2);
        range_apply(l, r, action, m + 1, b, cell_id * 2 + 1);
        pull(cell_id);
    }

    State query(int l, int r, int a, int b, int cell_id) {
        if (r < a || b < l) return e();
        if (l <= a && b <= r) return dat[cell_id];
        push(cell_id, a, b);
        int m = (a + b) / 2;
        State AnswerL = query(l, r, a, m, cell_id * 2);
        State AnswerR = query(l, r, m + 1, b, cell_id * 2 + 1);
        return op(AnswerL, AnswerR);
    }
};
]

ll N, M, Q, T;
vll A(500009);
string S;
int H, W;
vector<string> grid(300009);

int main() {
    // mainの最後で一括表示
    print_debug_log();
}

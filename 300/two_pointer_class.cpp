// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/300/two_pointer_class.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 尺取り法で得たい情報
struct TwoPointerInfo {
    int max_length = 0;
    int max_l = -1;
    int max_r = -1;
    ll interval_count = 0;
    ll total_length = 0;
};

// 区間内の異なる値が K 種類以下
struct KindsState {
private:
    int K;
    map<int, int> cnt;
    int current_kinds = 0;
    int max_kinds = 0;

public:
    explicit KindsState(int K) : K(K) {}

    bool can_add(int x) const {
        auto it = cnt.find(x);
        bool already_exists = (it != cnt.end() && it->second > 0);
        return already_exists || current_kinds < K;
    }

    void add(int x) {
        if (cnt[x] == 0) current_kinds++;
        cnt[x]++;
        max_kinds = max(max_kinds, current_kinds);
    }

    void remove(int x) {
        cnt[x]--;
        if (cnt[x] == 0) {
            current_kinds--;
            cnt.erase(x);
        }
    }

    int get_current_kinds() const {
        return current_kinds;
    }

    int get_max_kinds() const {
        return max_kinds;
    }
};

// 区間和が K 以下
// A の各要素が非負である場合に使う
struct SumState {
private:
    ll K;
    ll current_sum = 0;
    ll max_sum = 0;

public:
    explicit SumState(ll K) : K(K) {}

    bool can_add(int x) const {
        return (__int128)current_sum + x <= K;
    }

    void add(int x) {
        current_sum += x;
        max_sum = max(max_sum, current_sum);
    }

    void remove(int x) {
        current_sum -= x;
    }

    ll get_current_sum() const {
        return current_sum;
    }

    ll get_max_sum() const {
        return max_sum;
    }
};

// 区間内で、どの値も出現回数が K 回以下
// K = 1 とすれば、区間内の全要素が異なるという条件になる
struct FrequencyState {
private:
    int K;
    map<int, int> cnt;
    int max_frequency = 0;

public:
    explicit FrequencyState(int K) : K(K) {}

    bool can_add(int x) const {
        auto it = cnt.find(x);
        int frequency = (it == cnt.end() ? 0 : it->second);
        return frequency < K;
    }

    void add(int x) {
        cnt[x]++;
        max_frequency = max(max_frequency, cnt[x]);
    }

    void remove(int x) {
        cnt[x]--;
        if (cnt[x] == 0) cnt.erase(x);
    }

    int get_frequency(int x) const {
        auto it = cnt.find(x);
        return (it == cnt.end() ? 0 : it->second);
    }

    int get_max_frequency() const {
        return max_frequency;
    }
};

// 区間内の最大値 - 最小値が K 以下
struct RangeState {
private:
    ll K;
    multiset<int> values;
    ll max_range = 0;

    ll range_after_adding(int x) const {
        if (values.empty()) return 0;
        ll minimum = min<ll>(*values.begin(), x);
        ll maximum = max<ll>(*values.rbegin(), x);
        return maximum - minimum;
    }

public:
    explicit RangeState(ll K) : K(K) {}

    bool can_add(int x) const {
        return range_after_adding(x) <= K;
    }

    void add(int x) {
        values.insert(x);
        max_range = max(max_range, get_current_range());
    }

    void remove(int x) {
        values.erase(values.find(x));
    }

    ll get_current_range() const {
        if (values.empty()) return 0;
        return 1LL * (*values.rbegin()) - (*values.begin());
    }

    ll get_max_range() const {
        return max_range;
    }
};

// State は can_add(x), add(x), remove(x) を持つことを想定する
template <class State>
class SlidingWindow {
private:
    const vector<int>& A;  // 1-indexed
    int N;
    State state;

public:
    SlidingWindow(const vector<int>& A, State state)
        : A(A), N((int)A.size() - 1), state(std::move(state)) {}

    TwoPointerInfo solve() {
        TwoPointerInfo info;

        // 現在の区間は閉区間 [l, r]
        // r < l のときは空区間
        int l = 1;
        int r = 0;

        while (l <= N) {
            // 条件を満たす限り右端を伸ばす
            while (r + 1 <= N && state.can_add(A[r + 1])) {
                r++;
                state.add(A[r]);
            }

            // [l, r] は、左端が l である条件を満たす最大の区間
            int length = max(0, r - l + 1);

            // 条件を満たす区間が包含について閉じていることを仮定する
            info.interval_count += length;
            info.total_length += 1LL * length * (length + 1) / 2;

            if (length > info.max_length) {
                info.max_length = length;
                info.max_l = l;
                info.max_r = r;
            }

            // 左端を一つ進める
            if (l <= r) {
                state.remove(A[l]);
            } else {
                // A[l] 単体でも条件を満たさなかった場合、
                // 次のループも空区間から始める
                r = l;
            }
            l++;
        }

        return info;
    }

    const State& get_state() const {
        return state;
    }
};

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    // 条件に応じて State を差し替える
    SlidingWindow solver(A, KindsState(K));
    // SlidingWindow solver(A, SumState(K));
    // SlidingWindow solver(A, FrequencyState(K));
    // SlidingWindow solver(A, RangeState(K));

    TwoPointerInfo info = solver.solve();

    cout << info.max_length << '\n';
    // cout << solver.get_state().get_max_kinds() << '\n';
}

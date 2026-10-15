// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/High/SegmentTreeBeats/SegmentTreeBeats.cpp
// Segment Tree Beats.
// 区間chmin, 区間chmax, 区間加算, 区間和・最小値・最大値queryを扱う.
// 配列は1-indexed、区間は閉区間[l,r]で扱う.
// chmin/chmax/addを混ぜても償却O(log N)で動く.
class SegmentTreeBeats {
   private:
    using ll = long long;
    static constexpr ll NEG_INF = numeric_limits<ll>::lowest() / 4;
    static constexpr ll POS_INF = numeric_limits<ll>::max() / 4;

    struct State {
        ll sum;
        ll max_value;
        ll second_max_value;
        int max_count;
        ll min_value;
        ll second_min_value;
        int min_count;
    };

    vector<State> dat;
    vector<ll> lazy_add;
    int siz = 1;

    State make_leaf(ll x) {
        return {x, x, NEG_INF, 1, x, POS_INF, 1};
    }

    // 左右の区間Stateから親Stateを作る.
    State op(const State& left, const State& right) {
        State res;
        res.sum = left.sum + right.sum;

        if (left.max_value == right.max_value) {
            res.max_value = left.max_value;
            res.max_count = left.max_count + right.max_count;
            res.second_max_value = max(left.second_max_value, right.second_max_value);
        } else if (left.max_value > right.max_value) {
            res.max_value = left.max_value;
            res.max_count = left.max_count;
            res.second_max_value = max(left.second_max_value, right.max_value);
        } else {
            res.max_value = right.max_value;
            res.max_count = right.max_count;
            res.second_max_value = max(left.max_value, right.second_max_value);
        }

        if (left.min_value == right.min_value) {
            res.min_value = left.min_value;
            res.min_count = left.min_count + right.min_count;
            res.second_min_value = min(left.second_min_value, right.second_min_value);
        } else if (left.min_value < right.min_value) {
            res.min_value = left.min_value;
            res.min_count = left.min_count;
            res.second_min_value = min(left.second_min_value, right.min_value);
        } else {
            res.min_value = right.min_value;
            res.min_count = right.min_count;
            res.second_min_value = min(left.min_value, right.second_min_value);
        }
        return res;
    }

    void pull(int cell_id) {
        dat[cell_id] = op(dat[cell_id * 2], dat[cell_id * 2 + 1]);
    }

    // cell_idの最大値だけをxへ下げる. x > second_max_value が前提.
    void apply_chmin(int cell_id, ll x) {
        State& state = dat[cell_id];
        if (state.max_value <= x) return;
        state.sum += (x - state.max_value) * state.max_count;
        if (state.min_value == state.max_value) {
            state.min_value = x;
        } else if (state.second_min_value == state.max_value) {
            state.second_min_value = x;
        }
        state.max_value = x;
    }

    // cell_idの最小値だけをxへ上げる. x < second_min_value が前提.
    void apply_chmax(int cell_id, ll x) {
        State& state = dat[cell_id];
        if (x <= state.min_value) return;
        state.sum += (x - state.min_value) * state.min_count;
        if (state.max_value == state.min_value) {
            state.max_value = x;
        } else if (state.second_max_value == state.min_value) {
            state.second_max_value = x;
        }
        state.min_value = x;
    }

    void apply_add(int cell_id, ll x, int length) {
        State& state = dat[cell_id];
        state.sum += x * length;
        state.max_value += x;
        if (state.second_max_value != NEG_INF) state.second_max_value += x;
        state.min_value += x;
        if (state.second_min_value != POS_INF) state.second_min_value += x;
        lazy_add[cell_id] += x;
    }

    // 親に反映済みのadd/chmin/chmaxを子へ伝播する.
    void push(int cell_id, int a, int b) {
        if (a == b) return;
        int m = (a + b) / 2;
        if (lazy_add[cell_id] != 0) {
            apply_add(cell_id * 2, lazy_add[cell_id], m - a + 1);
            apply_add(cell_id * 2 + 1, lazy_add[cell_id], b - m);
            lazy_add[cell_id] = 0;
        }
        if (dat[cell_id * 2].max_value > dat[cell_id].max_value) {
            apply_chmin(cell_id * 2, dat[cell_id].max_value);
        }
        if (dat[cell_id * 2 + 1].max_value > dat[cell_id].max_value) {
            apply_chmin(cell_id * 2 + 1, dat[cell_id].max_value);
        }
        if (dat[cell_id * 2].min_value < dat[cell_id].min_value) {
            apply_chmax(cell_id * 2, dat[cell_id].min_value);
        }
        if (dat[cell_id * 2 + 1].min_value < dat[cell_id].min_value) {
            apply_chmax(cell_id * 2 + 1, dat[cell_id].min_value);
        }
    }

    void point_set(int array_id, ll x, int a, int b, int cell_id) {
        if (a == b) {
            dat[cell_id] = make_leaf(x);
            lazy_add[cell_id] = 0;
            return;
        }
        push(cell_id, a, b);
        int m = (a + b) / 2;
        if (array_id <= m) {
            point_set(array_id, x, a, m, cell_id * 2);
        } else {
            point_set(array_id, x, m + 1, b, cell_id * 2 + 1);
        }
        pull(cell_id);
    }

    void range_chmin(int l, int r, ll x, int a, int b, int cell_id) {
        if (r < a || b < l || dat[cell_id].max_value <= x) return;
        if (a == b) {
            apply_chmin(cell_id, x);
            return;
        }
        if (l <= a && b <= r && dat[cell_id].second_max_value < x) {
            apply_chmin(cell_id, x);
            return;
        }
        push(cell_id, a, b);
        int m = (a + b) / 2;
        range_chmin(l, r, x, a, m, cell_id * 2);
        range_chmin(l, r, x, m + 1, b, cell_id * 2 + 1);
        pull(cell_id);
    }

    void range_chmax(int l, int r, ll x, int a, int b, int cell_id) {
        if (r < a || b < l || x <= dat[cell_id].min_value) return;
        if (a == b) {
            apply_chmax(cell_id, x);
            return;
        }
        if (l <= a && b <= r && x < dat[cell_id].second_min_value) {
            apply_chmax(cell_id, x);
            return;
        }
        push(cell_id, a, b);
        int m = (a + b) / 2;
        range_chmax(l, r, x, a, m, cell_id * 2);
        range_chmax(l, r, x, m + 1, b, cell_id * 2 + 1);
        pull(cell_id);
    }

    void range_add(int l, int r, ll x, int a, int b, int cell_id) {
        if (r < a || b < l) return;
        if (l <= a && b <= r) {
            apply_add(cell_id, x, b - a + 1);
            return;
        }
        push(cell_id, a, b);
        int m = (a + b) / 2;
        range_add(l, r, x, a, m, cell_id * 2);
        range_add(l, r, x, m + 1, b, cell_id * 2 + 1);
        pull(cell_id);
    }

    ll query_sum(int l, int r, int a, int b, int cell_id) {
        if (r < a || b < l) return 0;
        if (l <= a && b <= r) return dat[cell_id].sum;
        push(cell_id, a, b);
        int m = (a + b) / 2;
        return query_sum(l, r, a, m, cell_id * 2) + query_sum(l, r, m + 1, b, cell_id * 2 + 1);
    }

    ll query_min(int l, int r, int a, int b, int cell_id) {
        if (r < a || b < l) return POS_INF;
        if (l <= a && b <= r) return dat[cell_id].min_value;
        push(cell_id, a, b);
        int m = (a + b) / 2;
        return min(query_min(l, r, a, m, cell_id * 2), query_min(l, r, m + 1, b, cell_id * 2 + 1));
    }

    ll query_max(int l, int r, int a, int b, int cell_id) {
        if (r < a || b < l) return NEG_INF;
        if (l <= a && b <= r) return dat[cell_id].max_value;
        push(cell_id, a, b);
        int m = (a + b) / 2;
        return max(query_max(l, r, a, m, cell_id * 2), query_max(l, r, m + 1, b, cell_id * 2 + 1));
    }

   public:
    // A[1]からA[N]を使って初期化する. A[0]は使わない.
    void build(const vector<ll>& A) {
        int N = static_cast<int>(A.size()) - 1;
        siz = 1;
        while (siz < N) siz *= 2;
        dat.assign(2 * siz, make_leaf(0));
        lazy_add.assign(2 * siz, 0);
        for (int i = 1; i <= N; i++) {
            dat[siz + i - 1] = make_leaf(A[i]);
        }
        for (int cell_id = siz - 1; cell_id >= 1; cell_id--) {
            pull(cell_id);
        }
    }

    void point_set(int array_id, ll x) { point_set(array_id, x, 1, siz, 1); }
    void range_chmin(int l, int r, ll x) { range_chmin(l, r, x, 1, siz, 1); }
    void range_chmax(int l, int r, ll x) { range_chmax(l, r, x, 1, siz, 1); }
    void range_add(int l, int r, ll x) { range_add(l, r, x, 1, siz, 1); }
    ll query_sum(int l, int r) { return query_sum(l, r, 1, siz, 1); }
    ll query_min(int l, int r) { return query_min(l, r, 1, siz, 1); }
    ll query_max(int l, int r) { return query_max(l, r, 1, siz, 1); }
};

// 使用例.
//   SegmentTreeBeats seg;
//   seg.build(A);                 // Aは1-indexed
//   seg.range_chmin(L, R, x); // A[L..R] = min(A[i], x)
//   seg.range_chmax(L, R, x); // A[L..R] = max(A[i], x)
//   seg.range_add(L, R, x);   // A[L..R] += x
//   long long ans = seg.query_sum(L, R);

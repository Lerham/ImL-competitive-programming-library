# 🔎 lower_bound / upper_bound の使い方

[`lower_upper_bound.cpp`](https://github.com/Lerham/ImL-competitive-programming-library/blob/main/300/lower_upper_bound.cpp) は `000/starter.cpp` を前提とします。関数を使うときは、出典リンクを含めて `main` より前に貼り付けます。このページの直接書く例だけなら、関数の貼り付けは不要です。

## 📌 前提

```cpp
ll N = 6;
vector<ll> x = {0, 1, 2, 2, 2, 5, 8}; // x[0] はダミー
// 対象は x[1] ... x[N]。昇順にする。
sort(x.begin() + 1, x.end());
ll value = 2;
```

`x.size() == N + 1` とし、`x[0]` は検索に含めません。空の場合も `x` はダミーだけを持ちます（`N = 0`）。以下はすべて添字 `i` を返します。

## 🎯 条件を満たす添字

```cpp
// x[i] >= value となる最小の i（この例では 2）
ll ge = lower_bound(x.begin() + 1, x.end(), value) - x.begin();

// x[i] > value となる最小の i（この例では 5）
ll gt = upper_bound(x.begin() + 1, x.end(), value) - x.begin();

// x[i] < value となる最大の i（この例では 1）
ll lt = lower_bound(x.begin() + 1, x.end(), value) - x.begin() - 1;

// x[i] <= value となる最大の i（この例では 4）
ll le = upper_bound(x.begin() + 1, x.end(), value) - x.begin() - 1;
```

| 探したい添字 | 書き方 | 存在しない場合 |
| --- | --- | --- |
| `value <= x[i]` の最小 `i` | `lower_bound(...) - x.begin()` | `N + 1` |
| `value < x[i]` の最小 `i` | `upper_bound(...) - x.begin()` | `N + 1` |
| `x[i] < value` の最大 `i` | `lower_bound(...) - x.begin() - 1` | `0` |
| `x[i] <= value` の最大 `i` | `upper_bound(...) - x.begin() - 1` | `0` |

表の `...` はすべて `x.begin() + 1, x.end(), value` です。`- 1` は **添字に変換した後**に行います。

```cpp
if (ge <= N) {
    ll answer = x[ge]; // 見つかった値
} else {
    // value 以上の要素はない
}
if (le >= 1) {
    ll answer = x[le]; // 見つかった値
} else {
    // value 以下の要素はない
}
```

⚠️ `N + 1` は配列外、`0` はダミーです。確認せずに `x[ge]` や `x[le]` を読まないこと。`lower_bound(...) - 1` とイテレータ自体を戻すと、先頭より前になってしまう場合があります。

## 🔢 個数と存在判定

```cpp
ll lb = lower_bound(x.begin() + 1, x.end(), value) - x.begin();
ll ub = upper_bound(x.begin() + 1, x.end(), value) - x.begin();

ll less       = lb - 1;     // x[i] <  value の個数
ll less_equal = ub - 1;     // x[i] <= value の個数
ll equal      = ub - lb;    // x[i] == value の個数
ll greater_equal = N + 1 - lb; // x[i] >= value の個数
ll greater       = N + 1 - ub; // x[i] >  value の個数

bool exists = (lb <= N && x[lb] == value); // value が存在するか
// または bool exists = (ub - lb > 0);
```

同じ値があれば、最初の添字は `lb`、最後の添字は `ub - 1` です。`lb == ub` なら存在しません。

## 📏 範囲に入る個数

`L <= R` のとき：

```cpp
ll lbL = lower_bound(x.begin() + 1, x.end(), L) - x.begin();
ll ubL = upper_bound(x.begin() + 1, x.end(), L) - x.begin();
ll lbR = lower_bound(x.begin() + 1, x.end(), R) - x.begin();
ll ubR = upper_bound(x.begin() + 1, x.end(), R) - x.begin();

ll closed = ubR - lbL;              // L <= x[i] <= R
ll left_closed = lbR - lbL;         // L <= x[i] <  R
ll right_closed = ubR - ubL;        // L <  x[i] <= R
ll open = max(0LL, lbR - ubL);      // L <  x[i] <  R
```

`L > R` のときは、これらの区間の個数を `0` として別に扱います。`L == R` の開区間も `0` です。

## 🧰 補助関数を使う場合

```cpp
ll lb = lower_bound_index(x, value); // x[i] >= value の最小 i
ll ub = upper_bound_index(x, value); // x[i] >  value の最小 i
ll le = ub - 1;                      // x[i] <= value の最大 i
ll lt = lb - 1;                      // x[i] <  value の最大 i
ll count = upper_bound_index(x, R) - lower_bound_index(x, L); // L <= R
```

どちらの関数も見つからなければ `N + 1` を返します。計算量はそれぞれ `O(log N)` です。

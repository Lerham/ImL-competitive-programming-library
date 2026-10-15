# Segment Tree の使い方

## まず貼り付ける

`starter/SegmentTreeStarter.cpp` を解答ファイルに貼り付けます。
`CustomState` の `Value`、`e()`、`leaf()`、`op()` を問題に合わせて編集します。

## 既製の状態を使う

区間和なら `starter/RSQstarter.cpp` を丸ごと貼り付けます。
最小値・最大値・積などの例は `States/` を見て、使う State の定義を
`SegmentTreeStarter.cpp` の `CustomState` と入れ替えます。

## 使う場所

```cpp
SegmentTree<CustomState> seg;
seg.init(N);
for (int i = 1; i <= N; i++) {
    seg.update(i, CustomState::leaf(A[i], i));
}

seg.update(p, CustomState::leaf(new_value, p)); // A[p] を置き換える
auto result = seg.query(l, r);                  // 閉区間 [l, r]
```

添字は **1-indexed**、区間は **閉区間 `[l, r]`** です。

// 0/1 ナップサック（重さDP）
//
// dp[j] := 重さ合計が j 以下になるように品物を選んだときの最大価値
//
// 計算量: O(NW)
//
// w[i], v[i] はそれぞれ品物 i の重さ・価値。
// w と v は 0-indexed で、同じサイズを想定。
ll knapsack_by_weight(
    const vector<ll>& w,
    const vector<ll>& v,
    int W
)
{
    vector<ll> dp(W + 1, 0);

    for (int i = 0; i < (int)w.size(); i++)
    {
        // 逆順に更新することで、品物 i を重複して使わない
        for (int j = W; j >= w[i]; j--)
        {
            dp[j] = max(
                dp[j],
                dp[j - w[i]] + v[i]
            );
        }
    }

    return dp[W];
}


// 0/1 ナップサック（価値DP）
//
// dp[value] := 合計価値をちょうど value にするための最小重量
//
// 計算量:
//   O(N * sum_v)
//
// w[i], v[i] はそれぞれ品物 i の重さ・価値。
// w と v は 0-indexed で、同じサイズを想定。
ll knapsack_by_value(
    const vector<ll>& w,
    const vector<ll>& v,
    ll W
)
{
    ll sum_v_ll = accumulate(v.begin(), v.end(), 0LL);

    // vector の添字とループ変数に int を使うため、
    // sum_v が int の範囲に収まることを想定。
    int sum_v = (int)sum_v_ll;

    const ll INF = 1LL << 60;

    vector<ll> dp(sum_v + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < (int)w.size(); i++)
    {
        // 逆順に更新することで、品物 i を重複して使わない
        for (int value = sum_v; value >= v[i]; value--)
        {
            if (dp[value - v[i]] == INF)
            {
                continue;
            }

            dp[value] = min(
                dp[value],
                dp[value - v[i]] + w[i]
            );
        }
    }

    // 重量制限 W 以下で実現できる最大価値を探す
    for (int value = sum_v; value >= 0; value--)
    {
        if (dp[value] <= W)
        {
            return value;
        }
    }

    return 0;
}
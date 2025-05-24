#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n;
vector<vector<int>> cost;
vector<vector<int>> dp;

// Hàm giải TSP bằng DP + Bitmask
int TSP(int mask, int u)
{
    if (mask == (1 << n) - 1)
        return cost[u][0]; // Quay lại thành phố đầu tiên
    if (dp[mask][u] != -1)
        return dp[mask][u];

    int res = INF;
    for (int v = 0; v < n; ++v)
    {
        if (!(mask & (1 << v)))
        { // Nếu chưa đi qua thành phố v
            res = min(res, cost[u][v] + TSP(mask | (1 << v), v));
        }
    }
    return dp[mask][u] = res;
}

int main()
{
    cin >> n;
    cost.assign(n, vector<int>(n));
    dp.assign(1 << n, vector<int>(n, -1));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> cost[i][j];

    cout << TSP(1, 0) << endl; // Bắt đầu từ thành phố 0, mask = 1 (chỉ đi qua thành phố 0)
    return 0;
}

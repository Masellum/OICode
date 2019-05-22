#include <cstdio>
#include <algorithm>

int n, m, v[30], w[30], c[30];
int dp[30005];
//01背包，dp[i][j]表示买前i件物品花了j元钱的时候得到的价格与重要度的乘积的总和的最大值
//dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + c[i]);

void init() {
    scanf("%d%d", &n, &m);
    int t1, t2;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &t1, &t2);
        v[i] = t1;
        w[i] = t2;
        c[i] = t1 * t2;
    }
    for (int i = 0; i <= m; ++i) {
        dp[i] = 0;
    }
}

int main() {
    init();
    for (int i = 1; i <= m; ++i) {
        for (int j = n; j >= v[i]; j--) {
            dp[j] = std::max(dp[j], dp[j - v[i]] + c[i]);
        }
    }
    printf("%d", dp[n]);
    return 0;
}

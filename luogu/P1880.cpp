#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 100 + 5;

int n, arr[4 * MAXN], dp[4 * MAXN][4 * MAXN], sum[4 * MAXN], ans;

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1880_2.in", "r", stdin);
    freopen("testdata/P1880_2.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = n + 1; i <= 2 * n; ++i) {
        arr[i] = arr[i - n];
    }
    for (int i = 1; i <= 2 * n; ++i) {
        sum[i] = sum[i - 1] + arr[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= 2 * n; ++i) {
        dp[i][i] = 0;
    }
    for (int l = 2 * n - 1; l >= 1; --l) {
        for (int r = l + 1; r < l + n; ++r) {
            for (int k = l; k < r; ++k) {
                dp[l][r] = std::min(dp[l][r], dp[l][k] + dp[k + 1][r] + sum[r] -
                                                  sum[l - 1]);
            }
        }
    }
    ans = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        ans = std::min(ans, dp[i][i + n - 1]);
    }
    printf("%d\n", ans);
    memset(dp, 0, sizeof(dp));
    for (int l = 2 * n - 1; l >= 1; --l) {
        for (int r = l + 1; r < l + n; ++r) {
            for (int k = l; k < r; ++k) {
                dp[l][r] = std::max(dp[l][r], dp[l][k] + dp[k + 1][r] + sum[r] -
                                                  sum[l - 1]);
            }
        }
    }
    ans = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        ans = std::max(ans, dp[i][i + n - 1]);
    }
    printf("%d", ans);
    return 0;
}
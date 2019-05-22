#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 50 + 5;

int m, n, map[MAXN][MAXN], dp[MAXN][MAXN][MAXN][MAXN], f[2 * MAXN][MAXN][MAXN];

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &map[i][j]);
        }
    }
    for (int s = 1; s <= m + n - 1; ++s) {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s - i + 1 < 1 || s - j + 1 < 1) {
                    continue;
                }
                f[s][i][j] =
                    std::max({f[s - 1][i][j], f[s - 1][i - 1][j],
                              f[s - 1][i][j - 1], f[s - 1][i - 1][j - 1]}) +
                    map[i][s - i + 1] + map[j][s - j + 1];
                if (i == j) {
                    f[s][i][j] -= map[i][s - i + 1];
                }
            }
        }
    }
    // for (int i = 1; i <= m; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         for (int k = 1; k <= m; ++k) {
    //             for (int l = j + 1; l <= n; ++l) {
    //                 dp[i][j][k][l] =
    //                     std::max(
    //                         {dp[i - 1][j][k - 1][l], dp[i - 1][j][k][l - 1],
    //                          dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1]}) +
    //                     map[i][j] + map[k][l];
    //             }
    //         }
    //     }
    // }
    // printf("%d", dp[m][n - 1][m - 1][n]);
    printf("%d", f[m + n - 1][m][m]);
    return 0;
}
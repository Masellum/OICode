#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 9 + 1;

int n, map[MAXN][MAXN], f[MAXN * 2][MAXN][MAXN];

int main() {
    scanf("%d", &n);
    int x, y, v;
    while (scanf("%d %d %d", &x, &y, &v), x != 0 && y != 0 && v != 0) {
        map[x][y] = v;
    }
    f[0][1][1] = map[1][1];
    for (int s = 1; s <= n + n - 2; ++s) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s - i + 2 < 1 || s - j + 2 < 1) {
                    continue;
                }
                f[s][i][j] =
                    std::max({f[s - 1][i][j - 1], f[s - 1][i - 1][j],
                              f[s - 1][i - 1][j - 1], f[s - 1][i][j]}) +
                    map[i][s - i + 2] + map[j][s - j + 2];
                if (i == j) {
                    f[s][i][j] -= map[i][s - i + 2];
                }
            }
        }
    }
    printf("%d", f[n + n - 2][n][n]);
    return 0;
}
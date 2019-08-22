#include <algorithm>
#include <cstdio>

#define ADD(a, b) ((1ll * (a) + (b)) % MOD)
#define MUL(a, b) ((1ll * (a) % MOD) * ((b) % MOD) % MOD)
#define C2(n) ((n) * ((n) - 1) / 2)

const int MAXN = 100 + 5, MOD = 9999973;

int n, m, f[MAXN][MAXN][MAXN], ans;

int main() {
    scanf("%d %d", &n, &m);
    f[1][0][0] = 1;
    f[1][1][0] = m;
    f[1][2][0] = m * (m - 1) / 2;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= m - j; ++k) {
                if (j + k > m) continue;
                f[i][j][k] = ADD(f[i][j][k], f[i - 1][j][k]); // 一个也不放
                if (j > 0) f[i][j][k] = ADD(f[i][j][k], MUL(f[i - 1][j - 1][k], m - j - k + 1)); // 在空列放一个
                if (k > 0 && j < m) f[i][j][k] = ADD(f[i][j][k], MUL(f[i - 1][j + 1][k - 1], j + 1)); // 在有一个的列放一个
                if (j > 1) f[i][j][k] = ADD(f[i][j][k], MUL(f[i - 1][j - 2][k], C2(m - j - k + 2))); // 在两个空列放两个
                if (j > 0 && k > 0) f[i][j][k] = ADD(f[i][j][k], MUL(f[i - 1][j][k - 1], MUL(m - j - k + 1, j))); // 在空列放一个 有一个的列放一个
                if (j + 2 <= m && k > 1) f[i][j][k] = ADD(f[i][j][k], MUL(f[i - 1][j + 2][k - 2], C2(j + 2))); // 在两个有一个的列放两个
            }
        }
    }
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i + j <= m) ans = ADD(ans, f[n][i][j]);
        }
    }
    printf("%d", ans);
    return 0;
}
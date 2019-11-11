#include <algorithm>
#include <cstdio>

const int MOD = 100000000;

int n, m;
int ans;

int f[13][1 << 13], g[13];

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1, x; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &x);
            g[i] = (g[i] << 1) | x;
        }
    }
    int max = (1 << n) - 1;
    f[0][0] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int S = 0; S <= max; ++S) {
            if ((S & (S << 1)) || (S & (S >> 1))) continue;
            if ((S & g[i]) != S) continue;
            for (int c = 0; c <= max; ++c) {
                if ((c & S) == 0) {
                    f[i][S] = (1ll * f[i][S] + f[i - 1][c]) % MOD;
                }
            }
        }
    }
    for (int S = 0; S <= max; ++S) {
        ans += f[m][S];
        ans %= MOD;
    }
    printf("%d", ans);
    return 0;
}
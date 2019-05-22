#include <cstdio>

int n, k;
int f[205][7];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        f[i][1] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= k; ++j) {
            f[i][j] = (i != j ? 0 : 1);
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= k; ++j) {
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
        }
    }
    printf("%d", f[n][k]);
    return 0;
}

#include <algorithm>
#include <cstdio>

const int MAX = 30 + 3;

int n, m, f[MAX][MAX];

int main() {
    scanf("%d %d", &n, &m);
    // f[0][1] = 1;
    // for (int i = 1; i <= m; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         f[i][j] = f[i - 1][(j - 1 + n) % n] + f[i - 1][(j + 1) % n];
    //     }
    // }
    // printf("%d", f[m][1]);
    f[1][0] = 1;
    for (int step = 1; step <= m; ++step) {
        for (int i = 1; i <= n + 1; ++i) {
            f[i % n][step] =
                f[(i + 1) % n][step - 1] + f[(i - 1 + n) % n][step - 1];
        }
    }
    printf("%d", f[1][m]);
    return 0;
}
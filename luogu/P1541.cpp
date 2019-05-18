#include <algorithm>
#include <cstdio>
#include <climits>

const int MAXN = 350 + 5, MAXM = 120 + 5;

using std::max;

int a[MAXN], b[MAXM], n, m, count[5], f[41][41][41][41];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &b[i]);
        count[b[i]]++;
    }
    f[0][0][0][0] = a[1];
    for (int i = 0; i <= count[1]; ++i) {
        for (int j = 0; j <= count[2]; ++j) {
            for (int k = 0; k <= count[3]; ++k) {
                for (int l = 0; l <= count[4]; ++l) {
                    int rest = a[1 + i + 2 * j + 3 * k + 4 * l];
                    if (i)
                        f[i][j][k][l] =
                            max(f[i][j][k][l], f[i - 1][j][k][l] + rest);
                    if (j)
                        f[i][j][k][l] =
                            max(f[i][j][k][l], f[i][j - 1][k][l] + rest);
                    if (k)
                        f[i][j][k][l] =
                            max(f[i][j][k][l], f[i][j][k - 1][l] + rest);
                    if (l)
                        f[i][j][k][l] =
                            max(f[i][j][k][l], f[i][j][k][l - 1] + rest);
                }
            }
        }
    }
    printf("%d", f[count[1]][count[2]][count[3]][count[4]]);
    return 0;
}
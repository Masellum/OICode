#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <numeric>

const int MAXN = 30 + 5;

int n, score[MAXN];
unsigned int ans;
unsigned int f[MAXN][MAXN];
int root[MAXN][MAXN];

void dfs(int x, int y) {
    if (x > y)
        return;
    printf("%d ", root[x][y]);
    if (x == y)
        return;
    dfs(x, root[x][y] - 1);
    dfs(root[x][y] + 1, y);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1040.in", "r", stdin);
    freopen("testdata/P1040.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", score + i);
    }
    for (int i = 1; i <= n; ++i) {
        root[i][i] = i;
        f[i][i - 1] = 1;
        f[i][i] = score[i];
    }
    f[n + 1][n] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            for (int k = i; k <= j; ++k) {
                if (f[i][k - 1] * f[k + 1][j] + score[k] > f[i][j]) {
                    f[i][j] = f[i][k - 1] * f[k + 1][j] + score[k];
                    root[i][j] = k;
                }
            }
        }
    }
    printf("%u\n", f[1][n]);
    dfs(1, n);
    return 0;
}
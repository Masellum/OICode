#include <algorithm>
#include <cstdio>

const int MAXN = 5000 + 5;

int n, f[MAXN][MAXN];
char s[MAXN];

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) {
        f[i][i] = 0;
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 1, j = i + len - 1; j <= n; ++i, ++j) {
            if (s[i] == s[j]) {
                f[i][j] = f[i + 1][j - 1];
            } else {
                f[i][j] = std::min(f[i][j - 1], f[i + 1][j]) + 1;
            }
        }
    }
    printf("%d", f[1][n]);
    return 0;
}
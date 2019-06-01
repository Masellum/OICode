#include <algorithm>
#include <cstdio>

const int MAXN = 2000 + 5;

int C[MAXN][MAXN];

int t, k, n, m;

int main() {
    std::scanf("%d %d", &t, &k);
    C[0][0] = 1;
    for (int i = 1; i <= 2000; ++i) {
        C[i][0] = C[i][1] = C[i][i] = 1;
    }
    for (int i = 3; i <= 2000; ++i) {
        for (int j = 2; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % k;
        }
    }
    while (t--) {
        std::scanf("%d %d", &n, &m);
        int ans = 0;
        for (int i = 0/*, min = std::min(i, m)*/; i <= n; ++i/*, min = std::min(i, m)*/) {
            int min = std::min(i, m);
            for (int j = 0; j <= min; ++j) {
                if (C[i][j] == 0) {
                    ++ans;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
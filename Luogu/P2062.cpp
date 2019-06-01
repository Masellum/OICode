#include <cstdio>
#include <climits>
#include <algorithm>

const int MAXN = 1000000 + 5;

int n, a[MAXN], f[MAXN], g[MAXN];

int main() {
    std::scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        std::scanf("%d", a + i);
    }
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i >= a[i]) {
            f[i] = g[i - a[i]] + 1;
        }
        g[i] = std::max(f[i], g[i - 1]);
    }
    std::printf("%d", f[n]);
    return 0;
}
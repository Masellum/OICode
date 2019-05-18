#include <cstdio>

const int MAXN = 100000 + 5;

int n, d[MAXN], ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", d + i);
    }
    for (int i = 0; i < n; ++i) {
        if (d[i + 1] > d[i]) {
            ans += d[i + 1] - d[i];
        }
    }
    printf("%d", ans);
    return 0;
}
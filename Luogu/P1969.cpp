#include <algorithm>
#include <cstdio>

const int MAXN = 100000 + 5;

int n, h[MAXN], now, ans, last;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &now);
        if (last < now) {
            ans += now - last;
        }
        last = now;
    }
    printf("%d", ans);
    return 0;
}
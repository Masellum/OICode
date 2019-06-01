#include <algorithm>
#include <cstdio>

int n, ans;

int main() {
    scanf("%d", &n);
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (r - l + 1) * (n / l);
    }
    printf("%d", ans);
    return 0;
}
#include <algorithm>
#include <cstdio>

int q;
long long l, r;

int main() {
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%lld %lld", &l, &r);
        int len = (r - l + 1) % 9, ans = 0;
        for (long long j = r - len + 1; j <= r; ++j) {
            ans = (ans + j % 9) % 9;
        }
        printf("%d\n", ans);
    }
    return 0;
}
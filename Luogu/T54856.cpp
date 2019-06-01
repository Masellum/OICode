#include <cstdio>
#include <algorithm>

const int MAXN = 300 + 5;

int n, h[MAXN];
long long ans;

int main() {
    std::scanf("%d", &n);
    std::for_each(h + 1, h + n + 1, [](int &n) { std::scanf("%d", &n); });
    std::sort(h + 1, h + n + 1);
    int l = 0, r = n;
    for (int i = 1; i <= n; ++i) {
        ans += (h[r] - h[l]) * (h[r] - h[l]);
        if (i & 1) {
            ++l;
        } else {
            --r;
        }
    }
    std::printf("%lld", ans);
    return 0;
}
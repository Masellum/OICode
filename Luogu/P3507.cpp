#include <algorithm>
#include <cstdio>

const int MAXN = 1000000 + 5;

int n, num[MAXN], f[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", num + i);
    }
    std::sort(num + 1, num + n + 1);
    f[1] = num[1];
    for (int i = 2; i <= n; ++i) {
        f[i] = std::max(f[i - 1], num[i] - f[i - 1]);
    }
    printf("%d", f[n]);
    return 0;
}
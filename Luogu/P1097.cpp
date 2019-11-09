#include <algorithm>
#include <cstdio>

const int MAXN = 200000 + 5;

int n, a[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    std::sort(a + 1, a + n + 1);
    for (int i = 2, last = 0; i <= n + 1; ++i) {
        if (a[i] != a[i - 1]) {
            printf("%d %d\n", a[i - 1], i - 1 - last);
            last = i - 1;
        }
    }
    return 0;
}
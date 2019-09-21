#include <algorithm>
#include <cstdio>

const int MAXN = 10000 + 5, MAXM = 1500 + 5;

char strs[MAXN][MAXM];

int n, a[MAXN], ans;

unsigned hash(char *str) {
    unsigned int base = 131;
    unsigned int h = 0;
    while (*str) { h = h * base + (*str++); }
    return (h & 0x7fffffff);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", strs[i]);
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = hash(strs[i]);
    }
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) if (a[i] != a[i - 1]) ans++;
    printf("%d", ans);
}
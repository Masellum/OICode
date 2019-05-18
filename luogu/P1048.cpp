#include <algorithm>
#include <cstdio>

const int MAX = 100 + 5;

int t, m, cost[MAX], value[MAX], f[MAX * 10];

int main() {
    scanf("%d %d", &t, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &cost[i], &value[i]);
    }
    std::fill(f + 1, f + t + 1, 0);
    for (int i = 1; i <= m; ++i) {
        for (int j = t; j >= cost[i]; --j) {
            f[j] = std::max(f[j], f[j - cost[i]] + value[i]);
        }
    }
    printf("%d", f[t]);
    return 0;
}
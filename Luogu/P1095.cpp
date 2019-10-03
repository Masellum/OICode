#include <algorithm>
#include <cstdio>

const int MAX = 300000 + 5;

int m, s, t;
long long f[MAX];

int main() {
    scanf("%d %d %d", &m, &s, &t);
    for (int i = 1; i <= t; ++i) {
        if (m >= 10) {
            f[i] = f[i - 1] + 60;
            m -= 10;
        } else {
            f[i] = f[i - 1];
            m += 4;
        }
    }
    for (int i = 1; i <= t; ++i) {
        f[i] = std::max(f[i], f[i - 1] + 17);
        if (f[i] >= s) return 0 * printf("Yes\n%d", i);
    }
    printf("No\n%d", f[t]);
    return 0;
}
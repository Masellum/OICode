#include <algorithm>
#include <cstdio>

const int MAXN = 100000 + 5, MOD = 100003;

int f[MAXN], n, k;

int main() {
    scanf("%d %d", &n, &k);
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = std::max(0, i - k); j < i; ++j) {
            f[i] = (f[i] % MOD + f[j] % MOD) % MOD;
        }
    }
    printf("%d", f[n]);
    return 0;
}
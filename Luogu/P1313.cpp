#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int MOD = 10007;

int a, b, k, n, m;
int combinations[1005][1005];

int fastPower(int x, int e) {
    int ret = 1, base = x;
    while (e) {
        if (e & 1) {
            ret = ((ret % MOD) * base) % MOD;
        }
        base = ((base % MOD) * (base % MOD)) % MOD;
        e >>= 1;
    }
    return ret;
}

void getCombinations(int n) {
    combinations[1][0] = 1;
    combinations[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
        combinations[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            combinations[i][j] =
                (combinations[i - 1][j - 1] + combinations[i - 1][j]) % MOD;
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &a, &b, &k, &n, &m);
    getCombinations(k);
    int ans = ((fastPower(a, n) % MOD) * (fastPower(b, m) % MOD)) % MOD;
    ans = (ans * (combinations[k][m] % MOD)) % MOD;
    printf("%d\n", ans);
    return 0;
}
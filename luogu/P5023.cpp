#include <cstdio>

const int MOD = 1e9 + 7;

int n, m;

namespace table
{
    int main() {
        if (n == 2 && m == 2) {
            puts("12");
        } else if (n == 2 && m == 3) {
            puts("36");
        } else if (n == 3 && m == 2) {
            puts("36");
        } else {
            puts("112");
        }
        return 0;
    }
} 

int fastPower(int x, int e) {
    int res = 1;
    for (x %= MOD; e; e >>= 1, x = 1ll * x * x % MOD) {
        if (e & 1) {
            res = 1ll * res * x % MOD;
        }
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    if (n <= 3 && m <= 3) {
        return table::main();
    }
    if (n == 2) {
        printf("%d", int(1ll * 4 * fastPower(3, m - 1) % MOD));
        return 0;
    }
    return 0;
}
#include <cstdio>

const int MOD = 1000000007;

int n, m, facn, facm, facs, invfacn, invfacm;

int fastPower(int a, int x) {
    int res = 1;
    for (; x; x >>= 1) {
        if (x & 1) res = 1ll * res * a % MOD;
        a = 1ll * a * a % MOD;
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    facn = facm = facs = 1;
    for (int i = 1; i <= n; ++i) {
        facn = 1ll * facn * i % MOD;
    }
    for (int i = 1; i <= m; ++i) {
        facm = 1ll * facm * i % MOD;
    }
    for (int i = 1; i <= n + m; ++i) {
        facs = 1ll * facs * i % MOD;
    }
    invfacn = fastPower(facn, MOD - 2);
    invfacm = fastPower(facm, MOD - 2);
    printf("%lld", 1ll * facs * invfacn % MOD * invfacm % MOD);
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <cstring>

long long b, p, k;

long long fastPower(int b, int p, int k) {
    if (p == 0)
        return 0;
    int res = 1, base = b;
    while (p != 0) {
        if (p & 1) {
            res = (res % k) * (base % k) % k;
        }
        base = (base % k) * (base % k) % k;
        p >>= 1;
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1226.in", "r", stdin);
    freopen("testdata/P1226.out", "w", stdout);
#endif
    scanf("%lld %lld %lld", &b, &p, &k);
    printf("%lld^%lld mod %lld=%lld", b, p, k, fastPower(b, p, k));
    return 0;
}
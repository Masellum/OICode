#include <algorithm>
#include <cstdio>

int n, m, k, x, ans;

int fastPower(int y, int e, int p) {
    int base = y, res = 1;
    for (; e; e >>= 1) {
        if (e & 1) {
            res = res % p * (base % p) % p;
        }
        base = base % p * (base % p) % p;
    }
    return res % p;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1965.in", "r", stdin);
    freopen("testdata/P1965.out", "w", stdout);
#endif
    scanf("%d %d %d %d", &n, &m, &k, &x);
    ans = fastPower(10, k, n);
    ans = ans * m % n;
    ans = (ans + x) % n;
    printf("%d", ans);
    return 0;
}
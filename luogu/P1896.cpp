#include <cstdio>
#include <iostream>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

typedef long long ll;

int n, k;
long long f[10][100][1025];

bool isValid(int s) {
    return (s & (s << 1)) == 0;
}

bool isValid(int s1, int s2) {
    return ((s1 << 1) & s2) == 0 && ((s2 << 1) & s1) == 0 && (s1 & s2) == 0;
}

int main() {
    std::scanf("%d %d", &n, &k);
    ll l = 1 << n;
    f[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            for (int t1 = 0; t1 < l; ++t1) {
                if (isValid(t1) && __builtin_popcount(t1) <= j) {
                    for (int t2 = 0; t2 < l; ++t2) {
                        if (isValid(t2) && isValid(t1, t2)/* && __builtin_popcount(t2) <= j*/) {
                            f[i][j][t1] += f[i - 1][j - __builtin_popcount(t1)][t2];
                        }
                    }
                }
            }
        }
    }
    ll ans = 0;
    for (int t = 0; t < l; ++t) {
        if (isValid(t)) {
            ans += f[n][k][t];
        }
    }
    std::printf("%lld", ans);
    return 0;
}
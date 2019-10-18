#include <algorithm>
#include <cstdio>
#include <numeric>

const int MAXN = 10000000 + 5;

int T, n, m;
int primes[700000], mu[MAXN], g[MAXN], cnt;
long long sumg[MAXN];
bool isNotPrime[MAXN];

void sieve(int s) {
    isNotPrime[1] = true;
    mu[1] = 1;
    for (int i = 2; i <= s; ++i) {
        if (!isNotPrime[i]) {
            primes[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * primes[j] <= s; ++j) {
            isNotPrime[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = -mu[i];
        }
    }
}

void calcg(int s) {
    for (int i = 1; i <= cnt; ++i) {
        for (int j = 1; primes[i] * j <= s; ++j) {
            g[primes[i] * j] += mu[j];
        }
    }
}

long long solve(int n, int m) {
    long long res = 0;
    for (int l = 1, r, s = std::min(n, m); l <= s; l = r + 1) {
        r = std::min(n / (n / l), m / (m / l));
        res += 1ll * (n / l) * (m / l) * (sumg[r] - sumg[l - 1]);
    }
    return res;
}

int main() {
    sieve(MAXN - 5);
    calcg(MAXN - 5);
    std::partial_sum(g + 1, g + MAXN - 4, sumg + 1);
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        printf("%lld\n", solve(n, m));
    }
    return 0;
}
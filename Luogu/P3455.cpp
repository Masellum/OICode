#include <algorithm>
#include <cstdio>
#include <numeric>

const int MAXN = 50000 + 5;

int N, a, b, d;
int primes[7000], mu[MAXN], summu[MAXN], cnt;
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

long long solve(int n, int m) {
    long long res = 0;
    for (int l = 1, r; l <= std::min(n, m); l = r + 1) {
        r = std::min(n / (n / l), m / (m / l));
        res += 1ll * (summu[r] - summu[l - 1]) * (n / l) * (m / l);
    }
    return res;
}

int main() {
    sieve(50000);
    std::partial_sum(mu + 1, mu + 50000 + 1, summu + 1);
    for (scanf("%d", &N); N; --N) {
        scanf("%d %d %d", &a, &b, &d);
        printf("%lld\n", solve(a / d, b / d));
    }
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <numeric>

#define POSI(x) (((x) + MOD) % MOD)

const int MAXN = 10000000 + 5, MOD = 20101009;

int n, m;
int primes[700000], mu[MAXN], mud[MAXN], summud[MAXN], sum[MAXN], cnt;
bool isNotPrime[MAXN];

void sieve(int s) {
    isNotPrime[1] = true;
    mud[1] = mu[1] = 1;
    for (int i = 2; i <= s; ++i) {
        if (!isNotPrime[i]) {
            primes[++cnt] = i;
            mu[i] = -1;
            mud[i] = POSI(1ll * i * i % MOD * mu[i]);
        }
        for (int j = 1; j <= cnt && i * primes[j] <= s; ++j) {
            isNotPrime[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                mud[i * primes[j]] = mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = -mu[i];
            mud[i * primes[j]] = POSI(1ll * i * primes[j] % MOD * i % MOD *
                                 primes[j] % MOD * mu[i * primes[j]] % MOD);
        }
    }
}

inline int t(int a, int b) {
    return 1ll * (1ll * a * (a + 1) / 2 % MOD) * (1ll * b * (b + 1) / 2 % MOD) % MOD;
}

int s(int a, int b) {
    int res = 0;
    for (int l = 1, r; l <= std::min(a, b); l = r + 1) {
        r = std::min(a / (a / l), b / (b / l));
        res = (1ll * (summud[r] - summud[l - 1]) % MOD * t(a / l, b / l) % MOD + res) % MOD;
    }
    return res;
}

int f(int a, int b) {
    int res = 0;
    for (int l = 1, r; l <= std::min(a, b); l = r + 1) {
        r = std::min(a / (a / l), b / (b / l));
        res = (1ll * (sum[r] - sum[l - 1]) * s(a / l, b / l) % MOD + res) % MOD;
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    if (n > m) std::swap(n, m);
    sieve(m);
    for (int i = 1; i <= m; ++i) {
        summud[i] = (1ll * summud[i - 1] + mud[i]) % MOD;
        sum[i] = (1ll * sum[i - 1] + i) % MOD;
    }
    printf("%d", POSI(f(n, m)));
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>

const int MAXN = 50000 + 5;

int N, a, b, c, d, k;
bool isNotPrime[MAXN];
int primes[6000], mu[MAXN], cnt;
int summu[MAXN], ans;

void sieve(int m) {
    isNotPrime[0] = isNotPrime[1] = true;
    mu[1] = 1;
    for (int i = 2; i <= m; ++i) {
        if (!isNotPrime[i]) {
            primes[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * primes[j] <= m; ++j) {
            isNotPrime[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = -mu[i];
        }
    }
}

int query(int n, int m) {
    int res = 0;
    for (int l = 1, r; l <= std::min(n, m); l = r + 1) {
        r = std::min(n / (n / l), m / (m / l));
        res += (summu[r] - summu[l - 1]) * (n / l) * (m / l);
    }
    return res;
}

int main() {
    sieve(50000);
    std::partial_sum(mu + 1, mu + 50000 + 1, summu + 1);
    scanf("%d", &N);
    while (N--) {
        scanf("%d %d %d %d %d", &a, &b, &c, &d, &k);
        ans = query(b / k, d / k) - query(b / k, (c - 1) / k) - query((a - 1) / k, d / k) + query((a - 1) / k, (c - 1) / k);
        printf("%d\n", ans);
    }
    return 0;
}
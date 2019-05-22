#include <algorithm>
#include <cstdio>

const int MAXN = 40000 + 5;

int n, ans;

bool isNotPrime[MAXN];
int primes[MAXN], cnt, phi[MAXN];

void sieve() {
    isNotPrime[0] = isNotPrime[1] = true;
    phi[1] = 1;
    for (int i = 1; i <= n; ++i) {
        if (!isNotPrime[i]) {
            primes[++cnt] = i;
            phi[i] = i - 1;
        }

        for (int j = 1; j <= cnt && i * primes[j] <= n; ++j) {
            isNotPrime[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = primes[j] * phi[i];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
}

int main() {
    scanf("%d", &n);
    if (n == 1) {
        puts("0");
        return 0;
    }
    sieve();
    for (int i = 1; i < n; ++i) {
        ans += phi[i];
    }
    ans = ans * 2 + 1;
    printf("%d", ans);
    return 0;
}
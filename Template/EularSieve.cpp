#include <algorithm>
#include <cstdio>

const int MAXM = 30000000;

int m;
bool isPrime[MAXM];
int primes[50000], cnt, phi[MAXM];

void sieve() {
    std::fill(isPrime + 1, isPrime + m + 1, true);
    isPrime[0] = isPrime[1] = false;
    phi[1] = 1;
    for (int i = 2; i <= m; ++i) {
        if (isPrime[i]) {
            primes[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt && i * primes[j] <= m; ++j) {
            isPrime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = primes[j] * phi[i];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
}

int main() {
    scanf("%d", &m);
    sieve();
    if (isPrime[m]) puts("YES");
    else puts("NO");
    return 0;
}
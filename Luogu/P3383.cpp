#include <algorithm>
#include <cstdio>

const int MAXN = 10000000 + 5;

bool isPrime[MAXN];
int primes[MAXN], cnt, n, m;

void sieve() {
    std::fill(isPrime + 1, isPrime + n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            primes[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * primes[j] <= n; ++j) {
            isPrime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    sieve();
    int q;
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &q);
        if (isPrime[q]) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}
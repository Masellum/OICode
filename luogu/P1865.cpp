#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>

const int MAXM = 1000000 + 5;
int n, m;

bool isPrime[MAXM];
int primes[7300], cnt, sum[MAXM];

void sieve() {
    std::fill(isPrime + 1, isPrime + m + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= m; ++i) {
        if (isPrime[i]) {
            primes[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * primes[j] <= m; ++j) {
            isPrime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1865.in", "r", stdin);
    freopen("testdata/P1865.out", "w", stdout);
#endif
    scanf("%d %d", &n, &m);
    sieve();
    for (int i = 1; i <= m; ++i) {
        sum[i] = sum[i - 1] + isPrime[i];
    }
    int l, r;
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &l, &r);
        if (1 <= l && l <= m && 1 <= r && r <= m) {
            printf("%d\n", sum[r] - sum[l - 1]);
        } else {
            puts("Crossing the line");
        }
    }
    return 0;
}
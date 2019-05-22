#include <algorithm>
#include <cstdio>

typedef long long ll;

const int MAXN = 3 * 1000000 + 5;

int n, p, inverse[MAXN];

int main() {
    scanf("%d %d", &n, &p);
    inverse[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inverse[i] = 1LL * (p - p / i) * inverse[p % i] % p;
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", inverse[i]);
    }
}
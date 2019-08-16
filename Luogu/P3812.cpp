#include <algorithm>
#include <cmath>
#include <cstdio>

const int MAXN = 50 + 5;

int n, maxBit;
long long a[MAXN], b[MAXN], ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
        if (a[i]) maxBit = std::max(maxBit, int(log2(a[i])));
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = maxBit; j >= 0; --j) {
            if (a[i] >> j & 1) {
                if (b[j]) a[i] ^= b[j];
                else {
                    b[j] = a[i];
                    for (int k = j - 1; k >= 0; --k) {
                        if (b[k] && (b[j] >> k & 1)) b[j] ^= b[k];
                    }
                    for (int k = j + 1; k <= maxBit; ++k) {
                        if (b[k] >> j & 1) b[k] ^= b[j];
                    }
                    break;
                }
            }
        }
    }
    for (int i = 0; i <= maxBit; ++i) {
        ans ^= b[i];
    }
    printf("%lld", ans);
    return 0;
}
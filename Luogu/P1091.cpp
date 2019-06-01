#include <algorithm>
#include <cstdio>
#include <climits>

const int MAXN = 100 + 5;

int n, t[MAXN], dp1[MAXN], dp2[MAXN], ans = INT_MIN;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", t + i);
    }
    std::fill(dp1 + 1, dp1 + n + 1, 1);
    std::fill(dp2 + 1, dp2 + n + 1, 1);
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (t[i] > t[j]) {
                dp1[i] = std::max(dp1[i], dp1[j] + 1);
            }
        }
    }
    for (int i = n - 1; i >= 1; --i) {
        for (int j = n; j > i; --j) {
            if (t[i] > t[j]) {
                dp2[i] = std::max(dp2[i], dp2[j] + 1);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        ans = std::max(ans, dp1[i] + dp2[i] - 1);
    }
    ans = n - ans;
    printf("%d", ans);
    return 0;
}
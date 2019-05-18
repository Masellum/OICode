#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

const int MAXN = 100 + 5;

struct Node {
    int a, b;
} node[MAXN * 2];

int n, necklace[MAXN * 2], dp[MAXN * 2][MAXN * 2], ans = INT_MIN;

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1063.in", "r", stdin);
    freopen("testdata/P1063.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &necklace[i]);
    }
    for (int i = 1; i <= n; ++i) {
        node[i].a = necklace[i];
    }
    for (int i = 1; i <= n; ++i) {
        node[i].b = node[i + 1].a;
    }
    node[n].b = node[1].a;
    for (int i = n + 1; i <= 2 * n; ++i) {
        node[i] = node[i - n];
    }
    for (int len = 2; len <= n; ++len) {
        for (int l = 1, r; l + len - 1 <= 2 * n; ++l) {
            r = l + len - 1;
            for (int k = l; k < r; ++k) {
                dp[l][r] =
                    std::max(dp[l][r], dp[l][k] + dp[k + 1][r] +
                                           node[l].a * node[k].b * node[r].b);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        ans = std::max(ans, dp[i][i + n - 1]);
    }
    printf("%d", ans);
    return 0;
}
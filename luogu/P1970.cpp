#include <algorithm>
#include <cstdio>
#include <climits>

#define lb(x) ((x) & (-(x)))

const int MAXN = 100000 + 5;

int n, h[MAXN], dp[2][MAXN];

int tree[MAXN * 10];

void modify(int x, int val) {
    for (; x <= n; x += lb(x)) {
        tree[x] = std::max(tree[x], val);
    }
}

int query(int x) {
    int res = INT_MIN;
    for (; x; x -= lb(x)) {
        res = std::max(res, tree[x]);
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", h + i);
    }
    dp[0][1] = dp[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
            if (h[i - 1] < h[i]) {
                dp[0][i] = dp[1][i - 1] + 1;
            } else {
                dp[0][i] = dp[0][i - 1];
            }
            if (h[i - 1] > h[i]) {
                dp[1][i] = dp[0][i - 1] + 1;
            } else {
                dp[1][i] = dp[1][i - 1];
            }
    }
    printf("%d", std::max(dp[0][n], dp[1][n]));
    return 0;
}
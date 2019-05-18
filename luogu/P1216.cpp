#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAX = 1000 + 5;

int triange[MAX][MAX], dp[MAX][MAX], r;

int main() {
    scanf("%d", &r);
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= i; ++j) {
            scanf("%d", &triange[i][j]);
        }
    }
    for (int i = 1; i <= r; ++i) {
        dp[r][i] = triange[r][i];
    }
    for (int i = r; i >= 1; --i) {
        for (int j = 1; j <= r; ++j) {
            dp[i - 1][j] = std::max(dp[i - 1][j], dp[i][j] + triange[i - 1][j]);
            dp[i - 1][j - 1] =
                std::max(dp[i - 1][j - 1], dp[i][j] + triange[i - 1][j - 1]);
        }
    }
    printf("%d", dp[1][1]);
    return 0;
}
// f[i][j]表示第一个串配对到i，第二个串配对到j时的最大长度；
// f[i][j] = max(f[i][j],
//               f[i - 1][j - 1] + w[s1[i]][s2[j]],
//               f[i - 1][j] + w[s1[i]][null],
//               f[i][j - 1] + w[null][s2[j]])

#include <algorithm>
#include <climits>
#include <cstdio>

const int MAX = 100 + 5;
const int TABLE[6][6] = {{0, 0, 0, 0, 0, 0},     {0, 5, -1, -2, -1, -3},
                         {0, -1, 5, -3, -2, -4}, {0, -2, -3, 5, -2, -2},
                         {0, -1, -2, -2, 5, -1}, {0, -3, -4, -2, -1, 0}};

inline int trans(char c) {
    if (c == 'A') {
        return 1;
    }
    if (c == 'C') {
        return 2;
    }
    if (c == 'G') {
        return 3;
    }
    if (c == 'T') {
        return 4;
    }
    return 0;
}

char s1[MAX], s2[MAX];
int lena, lenb;
int dp[MAX][MAX];

int main() {
#ifndef ONLINE_JUDGE
    freopen("./testdata/P1140.in", "r", stdin);
    freopen("./testdata/P1140.out", "w", stdout);
#endif
    scanf("%d%s", &lena, s1 + 1);
    scanf("%d%s", &lenb, s2 + 1);
    for (int i = 1; i <= lena; ++i) {
        for (int j = 1; j <= lenb; ++j) {
            dp[i][j] = INT_MIN;
        }
    }
    for (int i = 1; i <= lena; ++i) {
        dp[i][0] = dp[i - 1][0] + TABLE[trans(s1[i])][5];
    }
    for (int i = 1; i <= lenb; ++i) {
        dp[0][i] = dp[0][i - 1] + TABLE[5][trans(s2[i])];
    }
    for (int i = 1; i <= lena; ++i) {
        for (int j = 1; j <= lenb; ++j) {
            dp[i][j] = std::max(
                {dp[i][j], dp[i - 1][j] + TABLE[trans(s1[i])][5],
                 dp[i][j - 1] + TABLE[5][trans(s2[j])],
                 dp[i - 1][j - 1] + TABLE[trans(s1[i])][trans(s2[j])]});
        }
    }
    printf("%d", dp[lena][lenb]);
    return 0;
}
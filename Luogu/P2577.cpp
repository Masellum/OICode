#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

const int MAXN = 200 + 1;

struct Person {
    int g, e;

    bool operator<(const Person &that) const {
        return e > that.e;
    }
} person[MAXN];

int n, f[MAXN][MAXN * MAXN], sum[MAXN], ans = INT_MAX;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &person[i].g, &person[i].e);
    }
    std::sort(person + 1, person + n + 1);
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + person[i].g;
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= sum[i]; ++j) {
            if (j >= person[i].g) {
                f[i][j] = std::min(f[i][j], std::max(f[i - 1][j - person[i].g], j + person[i].e));
            }
            f[i][j] = std::min(f[i][j], std::max(f[i - 1][j], sum[i] - j + person[i].e));
        }
    }
    for (int i = 0; i <= sum[n]; ++i) {
        ans = std::min(ans, f[n][i]);
    }
    printf("%d", ans);
    return 0;
}
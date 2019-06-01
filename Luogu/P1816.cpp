#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(x) std::cerr << #x << "=" << x << std::endl
#endif

const int MAXN = 100000 + 5;

int n, q, s, l, minv[MAXN][18];

int main() {
    scanf("%d %d", &n, &q);
    memset(minv, 0x3f, sizeof(minv));
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &minv[i][0]);
    }
    for (int j = 1; j <= 17; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            minv[i][j] = std::min(minv[i][j - 1], minv[i + (1 << (j - 1))][j - 1]);
        }
    }
    for (int i = 1, len, mi; i <= q; ++i) {
        scanf("%d %d", &s, &l);
        len = l - s + 1;
        mi = std::min(minv[s][int(log2(len))], minv[l - (1 << (int(log2(len)))) + 1][int(log2(len))]);
        printf("%d ", mi);
    }
    return 0;
}

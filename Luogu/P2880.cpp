#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(x) std::cerr << #x << "=" << x << std::endl
#endif

const int MAXN = 50000 + 5;

int n, q, s, l, minv[MAXN][18], maxv[MAXN][18];

int main() {
    scanf("%d %d", &n, &q);
    memset(minv, 0x3f, sizeof(minv));
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &minv[i][0]);
        maxv[i][0] = minv[i][0];
    }
    for (int j = 1; j <= 17; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            minv[i][j] = std::min(minv[i][j - 1], minv[i + (1 << (j - 1))][j - 1]);
            maxv[i][j] = std::max(maxv[i][j - 1], maxv[i + (1 << (j - 1))][j - 1]);
        }
    }
    for (int i = 1, len, ma, mi; i <= q; ++i) {
        scanf("%d %d", &s, &l);
        len = l - s + 1;
        ma = std::max(maxv[s][int(log2(len))], maxv[l - (1 << (int(log2(len)))) + 1][int(log2(len))]);
        mi = std::min(minv[s][int(log2(len))], minv[l - (1 << (int(log2(len)))) + 1][int(log2(len))]);
#ifndef ONLINE_JUDGE
        printf("len=%d, int(log2(len))=%d, l - (1 << (int(log2(len))))=%d\n", len, int(log2(len)), l - (1 << (int(log2(len)))));
        DEBUG(maxv[s][int(log2(len))]);
        DEBUG(maxv[l - (1 << (int(log2(len))))][int(log2(len))]);
        DEBUG(minv[s][int(log2(len))]);
        DEBUG(minv[l - (1 << (int(log2(len))))][int(log2(len))]);
        printf("ma=%d\n", ma);
        printf("mi=%d\n", mi);
#endif
        printf("%d\n", ma - mi);
    }
    return 0;
}

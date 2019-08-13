#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 5000 + 1;

bool frontFacing[MAXN];
int d[MAXN], n, ansm = 0x3f3f3f3f, ansk;

int main() {
    scanf("%d", &n);
    char c = getchar();
    for (int i = 1; i <= n; ++i) {
        while (c != 'B' && c != 'F') c = getchar();
        frontFacing[i] = c == 'F';
        c = getchar();
    }
    for (int k = 1; k <= n; ++k) {
        memset(d, 0, sizeof(d));
        bool rev = false, failed = false;
        int m = 0;
        for (int i = 1; i <= n; ++i) {
            if (!(rev ^ frontFacing[i])) {
                if (i + k - 1 > n) {
                    failed = true;
                    break;
                }
                rev ^= 1;
                d[i + k - 1] = -1;
                m++;
            }
            if (d[i] == -1) {
                rev ^= 1;
            }
        }
        if (failed) continue;
        if (m < ansm) {
            ansm = m;
            ansk = k;
        }
    }
    printf("%d %d", ansk, ansm);
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 21;

int f[MAXN][MAXN][MAXN];

int cal(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0)
        return 1;
    if (a > 20 || b > 20 || c > 20)
        return cal(20, 20, 20);
    if (f[a][b][c])
        return f[a][b][c];
    if (a < b && b < c) {
        f[a][b][c] = cal(a, b, c - 1) + cal(a, b - 1, c - 1) - cal(a, b - 1, c);
        return f[a][b][c];
    } else {
        f[a][b][c] = cal(a - 1, b, c) + cal(a - 1, b - 1, c) +
                     cal(a - 1, b, c - 1) - cal(a - 1, b - 1, c - 1);
        return f[a][b][c];
    }
}

int main() {
    int a, b, c;
    f[0][0][0] = 1;
    scanf("%d %d %d", &a, &b, &c);
    while (a != -1 || b != -1 || c != -1) {
        printf("w(%d, %d, %d) = %d\n", a, b, c, cal(a, b, c));
        scanf("%d %d %d", &a, &b, &c);
    }
    return 0;
}
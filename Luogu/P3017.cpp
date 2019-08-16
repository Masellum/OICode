#include <algorithm>
#include <climits>
#include <cstdio>

const int MAXN = 500  + 5;

int rr, c, a, b, mat[MAXN][MAXN], sum[MAXN][MAXN];
int l = INT_MAX, r;

inline int getSum(int a, int b, int x, int y) {
    return sum[x][y] - sum[x][b - 1] - sum[a - 1][y] + sum[a - 1][b - 1];
}

bool judgeColomn(int n, int m, int x) {
    int res = 0;
    for (int last = 0, now = 1; now <= c; ++now) {
        if (sum[m][now] - sum[n][now] - sum[m][last] + sum[n][last] >= x) {
            res++;
            if (res >= b) return true;
            last = now;
        }
    }
    return false;
}

bool judgeRow(int x) {
    int res = 0;
    for (int last = 0, now = 1; now <= rr; ++now) {
        if (judgeColomn(last, now, x)) {
            res++;
            if (res >= a) return true;
            last = now;
        }
    }
    return false;
}

int main() {
    scanf("%d %d %d %d", &rr, &c, &a, &b);
    for (int i = 1; i <= rr; ++i) {
        for (int j = 1; j <= c; ++j) {
            scanf("%d", &mat[i][j]);
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mat[i][j];
            l = std::min(l, mat[i][j]);
        }
    }
    r = sum[rr][c];
    int mid, ans;
    while (l <= r) {
        mid = (l + r) / 2;
        if (judgeRow(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%d", ans);
    return 0;
}
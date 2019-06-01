#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>
#include <queue>

const int MAX = 500 + 5;

const int dx[] = {0, -1, 0, 1, 0}, dy[] = {0, 0, 1, 0, -1};

int n, m, mat[MAX][MAX], lmax[MAX][MAX], rmax[MAX][MAX], ans1, ansm;
bool vis[MAX][MAX], vism[MAX];

void dfs(int x, int y) {
    vis[x][y] = true;
    if (x == n) {
        vism[y] = true;
    }
    for (int i = 1; i <= 4; ++i) {
        int xx = x + dx[i], yy = y + dy[i];
        if (!(0 < xx && xx <= n) || !(0 < yy && yy <= m)) {
            continue;
        }
        if ((mat[xx][yy] >= mat[x][y])) {
            continue;
        }
        if ((!vis[xx][yy])) {
            dfs(xx, yy);
        }
        lmax[x][y] = std::min(lmax[x][y], lmax[xx][yy]);
        rmax[x][y] = std::max(rmax[x][y], rmax[xx][yy]);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1514.in", "r", stdin);
    freopen("testdata/P1514.out", "w", stdout);
#endif
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
    memset(lmax, 0x3f, sizeof(lmax));
    for (int i = 1; i <= m; ++i) {
        lmax[n][i] = i;
        rmax[n][i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        if (!vis[1][i]) {
            dfs(1, i);
        }
    }
    for (int i = 1; i <= m; ++i) {
        ansm += (bool)vism[i];
    }
    if (ansm != m) {
        puts("0");
        printf("%d\n", m - ansm);
        return 0;
    }
    int l = 1;
    while (l != m + 1) {
        int r = 0;
        for (int i = 1; i <= m; ++i) {
            if (lmax[1][i] <= l) {
                r = std::max(rmax[1][i], r);
            }
        }
        ans1++;
        l = r + 1;
    }
    puts("1");
    printf("%d\n", ans1);
    return 0;
}
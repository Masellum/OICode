#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 100 + 5;
const int dx[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1},
          dy[9] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
const char word[9] = "\0yizhong";

int n;
char map[MAXN][MAXN];
bool ok[MAXN][MAXN];

bool dfs(int x, int y, int dire, int dep) {
    if (map[x][y] != word[dep])
        return false;
    if (dep == 7) {
        return ok[x][y] = true;
    }
    bool okk = dfs(x + dx[dire], y + dy[dire], dire, dep + 1);
    ok[x][y] = ok[x][y] || okk;
    return okk;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1101.in", "r", stdin);
    freopen("testdata/P1101.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", map[i] + 1);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (map[i][j] == 'y') {
                for (int k = 1; k <= 8; ++k) {
                    ok[i][j] = dfs(i, j, k, 1) || ok[i][j];
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%c", ok[i][j] ? map[i][j] : '*');
        }
        puts("");
    }
    return 0;
}
/*
8
qyizhong
gydthkjy
nwidghji
orbzsfgz
hhgrhwth
zzzzzozo
iwdfrgng
yyyygggg
*/
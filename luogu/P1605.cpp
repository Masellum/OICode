#include <iostream>
#include <algorithm>

int n, m, t, sx, sy, fx, fy, ans;
int map[6][6];
int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, -1, 0, 1, 0};
bool vis[6][6];

void init() {
    std::cin >> n >> m >> t >> sx >> sy >> fx >> fy;
    int t1, t2;
    for (int i = 1; i <= t; ++i) {
        std::cin >> t1 >> t2;
        map[t1][t2] = -1;
    }
}

inline bool check(int x, int y) {
    return map[x][y] != -1 && !vis[x][y] && x >= 1 && x <= m && y >= 1 && y <= n;
}

void dfs(int x, int y) {
    vis[x][y] = true;
    if (x == fx && y == fy) {
        ans++;
        vis[x][y] = false;
        return;
    }
    for (int i = 1; i <= 4; ++i) {
        if (check(x + dx[i], y + dy[i])) {
            dfs(x + dx[i], y + dy[i]);
        }
    }
    vis[x][y] = false;
}

int main() {
    init();
    dfs(sx, sy);
    std::cout << ans << std::endl;
    return 0;
}

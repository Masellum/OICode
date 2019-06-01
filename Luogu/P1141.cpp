#include <algorithm>
#include <cstdio>
#include <queue>

const int MAXN = 1000 + 5;
const int dx[] = {0, 0, 1, 0, -1}, dy[] = {0, -1, 0, 1, 0};

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y){};
};

int n, m;
int connections[MAXN][MAXN], cnt, size[MAXN * MAXN];
char map[MAXN][MAXN];
bool vis[MAXN][MAXN];

void bfs(int x, int y) {
    std::queue<Point> q;
    vis[x][y] = true;
    connections[x][y] = ++cnt;
    size[cnt]++;
    q.push(Point(x, y));
    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        for (int i = 1; i <= 4; ++i) {
            // int nx = p.x + dx[i], ny = p.x + dy[i];
            int nx = p.x + dx[i], ny = p.y + dy[i];
            if (!vis[nx][ny] && nx > 0 && nx <= n && ny > 0 && ny <= n && map[nx][ny] != map[p.x][p.y]) {
                vis[nx][ny] = true;
                connections[nx][ny] = cnt;
                size[cnt]++;
                q.push(Point(nx, ny));
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", map[i] + 1);
    }
    int x, y;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        if (!connections[x][y]) {
            bfs(x, y);
        }
        printf("%d\n", size[connections[x][y]]);
    }
    return 0;
}
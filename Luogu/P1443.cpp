#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

struct Point {
    int first;
    int second;
    int depth;
};

int n, m, sx, sy;
int map[405][405];
bool vis[405][405];
int dx[9] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
int dy[9] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
std::queue<Point> q;

void init() {
    memset(map, -1, sizeof(map));
    std::cin >> n >> m >> sx >> sy;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; ++j) {
            map[i][j] = -1;
        }
    }
}

inline bool check(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && !vis[x][y];
}

Point tp, tpp;
int xx, yy, d;
void bfs(Point p) {
    p.depth = 0;
    q.push(p);
    vis[p.first][p.second] = true;
    while (!q.empty()) {
        tp = q.front();
        q.pop();
        map[tp.first][tp.second] = tp.depth;
        for (int i = 1; i <= 8; ++i) {
            xx = tp.first + dx[i], yy = tp.second + dy[i], d = tp.depth;
            if (check(xx, yy)) {
                tpp = (Point){xx, yy, d + 1};
                vis[xx][yy] = true;
                //                DEBUG(xx);DEBUG(yy);DEBUG(d);
                //                Sleep(500);
                //                map[xx][yy] = d + 1;
                q.push(tpp);
            }
        }
    }
}

int main() {
    init();
    bfs((Point){sx, sy, 0});
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cout << std::setw(5) << std::setiosflags(std::ios::left)
                      << map[i][j];
            //            printf("%-5d", map[i][j]);
        }
        std::cout << std::endl;
        //        printf("\n");
    }
    return 0;
}

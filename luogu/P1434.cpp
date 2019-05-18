#include <algorithm>
#include <climits>
#include <cstdio>

const int MAX = 100 + 3;
const int dx[] = {0, -1, 0, 1, 0}, dy[] = {0, 0, 1, 0, -1};

int map[MAX][MAX], longest[MAX][MAX];
int r, c, ans = INT_MIN;

void dfs(int x, int y) {
    if (longest[x][y])
        return;
    longest[x][y] = 1;
    for (int i = 1; i <= 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx > 0 && nx <= r && ny > 0 && ny <= c) {
            if (map[nx][ny] < map[x][y]) {
                dfs(nx, ny);
                longest[x][y] = std::max(longest[x][y], 1 + longest[nx][ny]);
            }
        }
    }
    ans = std::max(ans, longest[x][y]);
}

int main() {
    scanf("%d %d", &r, &c);
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            scanf("%d", &map[i][j]);
        }
    }
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            dfs(i, j);
        }
    }
    printf("%d", ans);
    return 0;
}
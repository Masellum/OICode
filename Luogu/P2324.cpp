#include <algorithm>
#include <cctype>
#include <cstdio>

const int GOAL[6][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1}, 
    {0, 0, 1, 1, 1, 1},
    {0, 0, 0, -1, 1, 1},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}
}, dx[9] = {0, 1, 2, 2, 1, -1, -2, -2, -1}, dy[9] = {0, 2, 1, -1, -2, -2, -1, 1, 2}, MAXDEPTH = 15;

int T, now[6][6], startX, startY;
bool success;

inline bool check(int x, int y) {
    return (x >= 1 && x <= 5) && (y >= 1 && y <= 5);
}

int evaluate() {
    int res = 0;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            if (now[i][j] != GOAL[i][j]) {
                res++;
            }
        }
    }
    return res;
}

void dfs(int x, int y, int depth, int maxDepth) {
    if (depth == maxDepth) {
        success = !evaluate();
        return;
    }
    for (int i = 1, nx, ny; i <= 8; ++i) {
        nx = x + dx[i];
        ny = y + dy[i];
        if (!check(nx, ny)) continue;
        std::swap(now[x][y], now[nx][ny]);
        if (evaluate() + depth <= maxDepth) {
            dfs(nx, ny, depth + 1, maxDepth);
            if (success) return;
        }
        std::swap(now[x][y], now[nx][ny]);
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        char c;
        success = false;
        for (int i = 1; i <= 5; ++i) {
            for (int j = 1; j <= 5; ++j) {
                c = getchar();
                while (!isdigit(c) && c != '*') c = getchar();
                if (c == '*') {
                    now[i][j] = -1;
                    startX = i, startY = j;
                } else {
                    now[i][j] = c - '0';
                }
            }
        }
        if (evaluate() == 0) {
            printf("0\n");
            continue;
        }
        for (int d = 1; d <= MAXDEPTH; ++d) {
            dfs(startX, startY, 0, d);
            if (success) {
                printf("%d\n", d);
                break;
            }
        }
        if (!success) {
            printf("-1\n");
        }
    }
    return 0;
}
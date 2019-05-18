#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

int sdk[10][10];
bool row[10][10], col[10][10], pal[10][10];
int score[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
    {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
    {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
    {0, 6, 7, 8, 9, 10, 9, 8, 7, 6},
    {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
    {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
    {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6},
};

inline int getPalace(int x, int y) {
    return ((x - 1) / 3) * 3 + ((y - 1) / 3) + 1;
}

void print() {
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            printf("%d ", sdk[i][j]);
        }
        puts("");
    }
}

void dfs(int x, int y) {
    if (sdk[x][y]) {
        if (x == 9 && y == 9) {
            print();
            exit(0);
        }
        if (y == 9) {
            dfs(x + 1, 1);
        } else {
            dfs(x, y + 1);
        }
    } else {
        int palace = getPalace(x, y);
        for (int i = 1; i <= 9; ++i) {
            if (!(row[x][i] || col[y][i] || pal[palace][i])) {
                sdk[x][y] = i;
                row[x][i] = true;
                col[y][i] = true;
                pal[palace][i] = true;
                if (x == 9 && y == 9) {
                    print();
                    exit(0);
                }
                if (y == 9) {
                    dfs(x + 1, 1);
                } else {
                    dfs(x, y + 1);
                }
                sdk[x][y] = 0;
                row[x][i] = false;
                col[y][i] = false;
                pal[palace][i] = false;
            }
        }
    }
}

int main() {
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            scanf("%d", &sdk[i][j]);
            if (sdk[i][j]) {
                row[i][sdk[i][j]] = true;
                col[j][sdk[i][j]] = true;
                pal[getPalace(i, j)][sdk[i][j]] = true;
            }
        }
    }
    dfs(1, 1);
    return 0;
}
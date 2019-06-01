#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

int n;
int map[35][35];
bool vis[35][35];
int qx[905];
int qy[905];
int head = 0;
int tail = head;
int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, -1, 0, 1, 0};

void push(int x, int y) {
    qx[tail] = x;
    qy[tail] = y;
    tail++;
}

void pop(int &x, int &y) {
    x = qx[head];
    y = qy[head];
    head++;
}

void cq() {
    memset(qx, 0, sizeof(qx));
    memset(qy, 0, sizeof(qy));
    head = 0;
    tail = head;
}

void init() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> map[i][j];
        }
    }
}

inline bool check(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n && !vis[x][y] && map[x][y] == 0;
}

void bfs(int sx, int sy) {
    push(sx, sy);
    vis[sx][sy] = true;
    int tx, ty;
    while (head != tail) {
        pop(tx, ty);
        for (int i = 1; i <= 4; ++i) {
            if (check(tx + dx[i], ty + dy[i])) {
                push(tx + dx[i], ty + dy[i]);
                vis[tx + dx[i]][ty + dy[i]] = true;
            }
        }
    }
}

int main() {
    init();
    for (int i = 1; i <= n; ++i) {
        if (map[1][i] == 0 && !vis[1][i]) {
            bfs(1, i);
        }
    }
    cq();
    for (int i = 1; i <= n; ++i) {
        if (map[n][i] == 0 && !vis[n][i]) {
            bfs(n, i);
        }
    }
    cq();
    for (int i = 2; i < n; ++i) {
        if (map[i][1] == 0 && !vis[i][1]) {
            bfs(i, 1);
        }
    }
    cq();
    for (int i = 2; i < n; ++i) {
        if (map[i][n] == 0 && !vis[i][n]) {
            bfs(i, n);
        }
    }
    cq();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (map[i][j] != 1 && !vis[i][j]) {
                map[i][j] = 2;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cout << map[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}

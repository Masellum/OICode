#include <ctime>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <algorithm>

const int MAXN = 10000 + 5;

int fa[MAXN], rank[MAXN], n, m;

int find(int x) {
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (rank[x] > rank[y])
        std::swap(x, y);
    if (rank[x] < rank[y]) {
        fa[x] = y;
    } else {
        if (rand() % 2 > 1) {
            fa[x] = y;
            rank[y]++;
        } else {
            fa[y] = x;
            rank[x]++;
        }
    }
}

int main() {
    srand(time(NULL));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    int z, x, y;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &z, &x, &y);
        if (z == 1)
            merge(x, y);
        else if (z == 2) {
            x = find(x);
            y = find(y);
            if (x == y)
                printf("Y\n");
            else
                printf("N\n");
        }
    }
    return 0;
}
#include <cmath>
#include <cstdio>
#include <algorithm>

const int MAX = 500000 + 5;

int n, m, s;

int from[2 * MAX], to[2 * MAX], head[MAX], next[2 * MAX], cnt;
int f[MAX][20], log_2[MAX], dep[MAX];
bool vis[MAX];

void addEdge(int f, int t) {
    from[++cnt] = f;
    to[cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
}

void init() {
    for (int i = 1; i <= n; ++i) {
        log_2[i] = log_2[i - 1] + (1 << log_2[i - 1] == i);
    }
}

void dfs(int x, int fa) {
    vis[x] = true;
    f[x][0] = fa;
    dep[x] = dep[fa] + 1;
    for (int j = 1; (1 << j) <= dep[x]; ++j) {
        f[x][j] = f[f[x][j - 1]][j - 1];
    }
    for (int e = head[x]; e; e = next[e]) {
        if (!vis[to[e]]) {
            dfs(to[e], x);
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    while (dep[x] > dep[y]) {
        x = f[x][log_2[dep[x] - dep[y]] - 1];
    }
    if (x == y) return x;
    for (int j = log_2[dep[x]]; j >= 0; --j) {
        if (f[x][j] == f[y][j]) continue;
        x = f[x][j];
        y = f[y][j];
    }
    return f[x][0];
}

int main() {
    scanf("%d %d %d", &n, &m, &s);
    int x, y;
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }
    init();
    dfs(s, 0);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        printf("%d\n", lca(x, y));
    }
    return 0;
}

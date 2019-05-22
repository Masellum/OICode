#include <algorithm>
#include <cstdio>

const int MAXN = 100000 + 5;

int n, q;
int head[MAXN], from[2 * MAXN], to[2 * MAXN], next[2 * MAXN], cnt;
int d[MAXN], f[MAXN][19];

void addEdge(int f, int t) {
    from[++cnt] = f;
    to[cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
}

void dfs(int u, int fa) {
    f[u][0] = fa;
    d[u] = d[fa] + 1;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa)
            continue;
        dfs(v, u);
    }
}

void prework() {
    for (int j = 1; j <= 18; ++j) {
        for (int i = 1; i <= n; ++i) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
}

int getLCA(int u, int v) {
    if (d[u] < d[v])
        std::swap(u, v);
    for (int j = 18; j >= 0; --j) {
        if (d[f[u][j]] >= d[v])
            u = f[u][j];
    }
    if (u == v)
        return u;
    for (int j = 18; j >= 0; --j) {
        if (f[u][j] != f[v][j]) {
            u = f[u][j];
            v = f[v][j];
        }
    }
    return f[u][0];
}

int dis(int u, int v) {
    int lca = getLCA(u, v);
    return d[u] + d[v] - 2 * d[lca];
}

bool check(int x, int y, int u, int v) {
    int a = getLCA(x, y), b = getLCA(u, v);
    return (dis(a, u) + dis(a, v) == dis(u, v) ||
            dis(b, x) + dis(b, y) == dis(x, y));
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v), addEdge(v, u);
    }
    dfs(1, 0);
    prework();
    for (int i = 1, x, y, u, v; i <= q; ++i) {
        scanf("%d%d%d%d", &x, &y, &u, &v);
        if (check(x, y, u, v)) {
            puts("Y");
        } else {
            puts("N");
        }
    }
    return 0;
}
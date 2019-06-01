#include <cstdio>
#include <algorithm>

const int MAX = 300000;
int n, m;
int head[MAX], from[MAX * 2], to[MAX * 2], next[MAX], cnt;
int depth[MAX], f[MAX][20], w[MAX];
int bucket[MAX * 2], ans[MAX];

struct Path {
    int u, v;
    Path() {}
    Path(int u, int v) : u(u), v(v) {}
} path[MAX];

void addEdge(int f, int t) {
    from[++cnt] = f;
    to[cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
    to[++cnt] = f;
    from[cnt] = t;
    next[cnt] = head[t];
    head[t] = cnt;
}

void dfs1(int u, int father) {
    f[u][0] = father;
    depth[u] = depth[father] + 1;
    for (int e = head[u]; e; e = next[e]) {
        int v = to[e];
        if (v == father) {
            continue;
        }
        dfs1(v, u);
    }
}

void preworkLCA() {
    for (int j = 1; j <= 19; ++j) {
        for (int i = 1; i <= n; ++i) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
}

int getLCA(int x, int y) {
    if (depth[x] < depth[y]) {
        std::swap(x, y);
    }
    for (int j = 19; j >= 0; --j) {
        if (depth[f[x][j]] >= depth[y]) {
            x = f[x][j];
        }
    }
    if (x == y) {
        return x;
    }
    for (int j = 19; j >= 0; --j) {
        if (f[x][j] != f[y][j]) {
            x = f[x][j];
            y = f[y][j];
        }
    }
    return f[x][0];
}

void dfs2(int u, int father) {
    int formerVal = bucket[depth[u] + w[u]];
    for (int e = head[u]; e; e = next[e]) {
        int v = to[e];
        if (v == father) {
            continue;
        }
        dfs2(u, father);
    }
    int nowans = bucket[depth[u] + w[u]] - formerVal;
    ans[u] += nowans;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", w + i);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &path[i].u, &path[i].v);
    }
    dfs1(1, 0);
    preworkLCA();
}
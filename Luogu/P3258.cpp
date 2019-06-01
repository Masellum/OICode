#include <algorithm>
#include <cstdio>

const int MAXN = 300000 + 5;

int head[MAXN], to[MAXN * 2], next[MAXN * 2], cnt;
int depth[MAXN], f[MAXN][20];
int diff[MAXN];

int n, a[MAXN];

void addEdge(int f, int t) {
    to[++cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
    to[++cnt] = f;
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
        if (f[x][j] == f[y][j]) {
            continue;
        }
        x = f[x][j];
        y = f[y][j];
    }
    return f[x][0];
}

void setDiff(int x, int y) {
    int lca = getLCA(x, y);
    diff[x]++;
    diff[y]++;
    diff[lca]--;
    diff[f[lca][0]]--;
}

void dfs2(int u, int father) {
    for (int e = head[u]; e; e = next[e]) {
        int v = to[e];
        if (v == father) {
            continue;
        }
        dfs2(v, u);
        diff[u] += diff[v];
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("./testdata/P3258.in", "r", stdin);
    freopen("testdata/P3258.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 1, x, y; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addEdge(x, y);
    }
    dfs1(1, 0);
    preworkLCA();
    for (int i = 1; i < n; ++i) {
        setDiff(a[i], a[i + 1]);
    }
    dfs2(1, 0);
    for (int i = 2; i <= n; ++i) {
        diff[a[i]]--;
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", diff[i]);
    }
    return 0;
}
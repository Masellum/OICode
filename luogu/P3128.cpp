#include <algorithm>
#include <cstdio>
#include <climits>

const int MAXN = 50000 + 5;

int head[MAXN], to[MAXN * 2], next[MAXN * 2], cnt;
int f[MAXN][17], depth[MAXN];
int c[MAXN], ans = INT_MIN;

void addEdge(int f, int t) {
    to[++cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
    to[++cnt] = f;
    next[cnt] = head[t];
    head[t] = cnt;
}

int n, k;

void dfs(int u, int father) {
    f[u][0] = father;
    depth[u] = depth[father] + 1;

    for (int e = head[u]; e; e = next[e]) {
        int v = to[e];
        if (v == father) {
            continue;
        }
        dfs(v, u);
    }
}

void prework() {
    for (int j = 1; j <= 16; ++j) {
        for (int i = 1; i <= n; ++i) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
}

int getLCA(int x, int y) {
    if (depth[x] < depth[y]) {
        std::swap(x, y);
    }
    for (int j = 16; j >= 0; --j) {
        if (depth[f[x][j]] >= depth[y]) {
            x = f[x][j];
        }
    }
    if (x == y) {
        return x;
    }
    for (int j = 16; j >= 0; --j) {
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
    c[x]++;
    c[y]++;
    c[lca]--;
    c[f[lca][0]]--;
}

void process(int u, int father) {
    for (int e = head[u], v; e; e = next[e]) {
        v = to[e];
        if (v == father) {
            continue;
        }
        process(v, u);
        c[u] += c[v];
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    dfs(1, 0);
    prework();
    for (int i = 1, s, t; i <= k; ++i) {
        scanf("%d %d", &s, &t);
        setDiff(s, t);
    }
    process(1, 0);
    for (int i = 1; i <= n; ++i) {
        ans = std::max(ans, c[i]);
    }
    printf("%d", ans);
    return 0;
}
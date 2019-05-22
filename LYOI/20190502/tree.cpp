#include <algorithm>
#include <cstdio>

const int MAXN = 200000 + 5;

int n, q;
int to[MAXN], next[2 * MAXN], head[2 * MAXN], cnt;
int dfn[MAXN], size[MAXN], ts;

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    dfn[u] = ++ts;
    size[u] = 1;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa)
            continue;
        dfs(v, u);
        size[u] += size[v];
    }
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1, x, y; i < n; ++i) {
        scanf("%d%d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }
    dfs(1, 0);
    scanf("%d", &q);
    for (int i = 1, x, y, z; i <= q; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        int u = to[2 * z], v = to[2 * z - 1], w = ((dfn[u] > dfn[v]) ? u : v);
        if ((dfn[x] < dfn[w] && dfn[y] < dfn[w]) ||
            (dfn[x] >= dfn[w] + size[w] && dfn[y] >= dfn[w] + size[w]) ||
            (dfn[x] < dfn[w] && dfn[y] >= dfn[w] + size[w]) ||
            (dfn[x] >= dfn[w] + size[w] && dfn[u] < dfn[w]) ||
            (dfn[x] >= dfn[w] && dfn[x] < dfn[w] + size[w] &&
             dfn[y] >= dfn[w] && dfn[y] < dfn[w] + size[w])) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
#include <algorithm>
#include <cstdio>

const int MAXN = 100000 + 5;

int n, q;
int weight[MAXN], head[MAXN], to[2 * MAXN], next[2 * MAXN], ecnt;
int fa[MAXN], dep[MAXN], mson[MAXN], size[MAXN], top[MAXN], dfn[MAXN], ts;
int root[MAXN], son[30 * MAXN][2], cnt[30 * MAXN], tail;

void addEdge(int u, int v) {
    to[++ecnt] = v;
    next[ecnt] = head[u];
    head[u] = ecnt;
}

void add(int fm, int rt, int x, int d) {
    cnt[rt] = cnt[fm] + 1;
    if (d < 0) return;
    int f = (x >> d) & 1;
    son[rt][!f] = son[fm][!f];
    add(son[fm][f], son[rt][f] = ++tail, x, d - 1);
}

int query(int L, int R, int x, int d) {
    if (d < 0) return 0;
    int f = (x >> d) & 1;
    if (cnt[son[R][!f]] > cnt[son[L][!f]])
        return (1 << d) + query(son[L][!f], son[R][!f], x, d - 1);
    else return query(son[L][f], son[R][f], x, d - 1);
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    size[u] = 1;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[mson[u]]) mson[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++ts;
    add(root[ts - 1], root[ts] = ++tail, weight[u], 30);
    if (!mson[u]) return;
    dfs2(mson[u], t);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa[u] || v == mson[u]) continue;
        dfs2(v, v);
    }
}

int query(int x, int y) {
    return query(root[dfn[x] - 1], root[dfn[x] + size[x] - 1], y, 30);
}

int query(int u, int v, int z) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        res = std::max(res, query(root[dfn[top[u]] - 1], root[dfn[u]], z, 30));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) std::swap(u, v);
    res = std::max(res, query(root[dfn[u] - 1], root[dfn[v]], z, 30));
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", weight + i);
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1, opt, x, y, z; i <= q; ++i) {
        scanf("%d %d %d", &opt, &x, &y);
        if (opt == 1) printf("%d\n", query(x, y));
        else scanf("%d", &z), printf("%d\n", query(x, y, z));
    }
    return 0;
}
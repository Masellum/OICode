#include <algorithm>
#include <cstdio>

char buf[1 << 20], *p1, *p2;

// #define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin)) ? EOF : *p1++)
#define gc() getchar_unlocked()

template <class T>
void read(T &x) {
    x = 0;
    register char c = gc();
    register bool f = false;
    while ('0' > c || c > '9') if (c == '-') f = true, c = gc();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = gc();
    if (f) x = -x;
}

const int MAXN = 200000 + 5, MAX = 2e9;

// int n, m;
// int n, m, lastans;
// int n, m, B[MAXN], len;
int n, m, B[MAXN], len, lastans;
int head[MAXN], to[2 * MAXN], next[2 * MAXN], ecnt;
int weight[MAXN], fa[MAXN], dep[MAXN], top[MAXN], son[MAXN], size[MAXN], dfn[MAXN], ts;

void addEdge(int u, int v) {
    to[++ecnt] = v;
    next[ecnt] = head[u];
    head[u] = ecnt;
}

struct PST {
#define mid ((l + r) >> 1)
    int root[MAXN], lc[MAXN << 5], rc[MAXN << 5], sum[MAXN << 5], tail;

    void insert(int former, int &rt, int l, int r, int x) {
        sum[rt] = sum[former] + 1;
        if (l == r) return;
        if (x <= mid) rc[rt] = rc[former], insert(lc[former], lc[rt] = ++tail, l, mid, x);
        else lc[rt] = lc[former], insert(rc[former], rc[rt] = ++tail, mid + 1, r, x);
    }

    int query(int fa, int former, int L, int R, int l, int r, int k) {
        if (l == r) return l;
        int lsum = sum[lc[L]] + sum[lc[R]] - sum[lc[former]] - sum[lc[fa]];
        if (k <= lsum) return query(lc[fa], lc[former], lc[L], lc[R], l, mid, k);
        else return query(rc[fa], rc[former], rc[L], rc[R], mid + 1, r, k - lsum);
    }
#undef mid
} seg;

void dfs1(int u, int f) {
    dfn[u] = ++ts;
    fa[u] = f;
    dep[u] = dep[f] + 1;
    size[u] = 1;
    // seg.insert(seg.root[dfn[f]], seg.root[ts] = ++seg.tail, -MAX, MAX, weight[u]);
    seg.insert(seg.root[dfn[f]], seg.root[ts] = ++seg.tail, 1, len, std::lower_bound(B + 1, B + len + 1, weight[u]) - B);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int getLCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) std::swap(u, v);
    return u;
}

int query(int u, int v, int k) {
    int lca = getLCA(u, v);
    // return seg.query(seg.root[dfn[fa[lca]]], seg.root[dfn[lca]], seg.root[dfn[u]], seg.root[dfn[v]], -MAX, MAX, k);
    return seg.query(seg.root[dfn[fa[lca]]], seg.root[dfn[lca]], seg.root[dfn[u]], seg.root[dfn[v]], 1, len, k);
}

int main() {
#ifdef _LOCAL
    freopen("./testdata/P2633.in", "r", stdin);
    freopen("./testdata/P2633.out", "w", stdout);
#endif
    // scanf("%d %d", &n, &m);
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        read(weight[i]);
        B[i] = weight[i];
        // scanf("%d", weight + i);
    }
    std::sort(B + 1, B + n + 1);
    len = std::unique(B + 1, B + n + 1) - B - 1;
    for (int i = 1, u, v; i < n; ++i) {
        read(u), read(v);
        // scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1, u, v, k; i <= m; ++i) {
        read(u), read(v), read(k);
        // scanf("%d %d %d", &u, &v, &k);
        // printf("%d\n", query(u, v, k));
        // printf("%d\n", B[query(u, v, k)]);
        // printf("%d\n", B[lastans = query(u ^ lastans, v, k)]);
        lastans = B[query(u ^ lastans, v, k)];
        printf("%d\n", lastans);
        // printf("%d\n", lastans);
    }
    return 0;
}
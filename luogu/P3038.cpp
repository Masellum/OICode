#include <algorithm>
#include <cstdio>

#define LC (root * 2)
#define RC (root * 2 + 1)

const int MAXN = 100000 + 5;

int n, m;
int head[MAXN], to[MAXN * 2], next[MAXN * 2], cnt;
int fa[MAXN], dep[MAXN], size[MAXN], son[MAXN], dfn[MAXN], pos[MAXN], top[MAXN],
    ts;

void addEdge(int f, int t) {
    to[++cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    size[u] = 1;
    son[u] = -1;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == f)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        if (son[u] == -1 || size[v] > size[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int t) {
    dfn[u] = ++ts;
    pos[ts] = u;
    top[u] = t;
    if (son[u] == -1)
        return;
    dfs2(son[u], t);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}

struct SegmentTree {
    long long sum[MAXN * 4], tag[MAXN * 4];

    void pushUp(int root) { sum[root] = sum[LC] + sum[RC]; }

    void build(int root, int l, int r) {
        if (l == r) {
            sum[root] = 0;
            tag[root] = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(LC, l, mid);
        build(RC, mid + 1, r);
        pushUp(root);
    }

    void cover(int root, int l, int r, long long d) {
        tag[root] += d;
        sum[root] += 1ll * (r - l + 1) * d;
    }

    void pushDown(int root, int l, int r) {
        if (tag[root] && l != r) {
            int mid = (l + r) / 2;
            cover(LC, l, mid, tag[root]);
            cover(RC, mid + 1, r, tag[root]);
            tag[root] = 0;
        }
    }

    void modifyAdd(int root, int l, int r, int left, int right, long long d) {
        if (l == left && r == right) {
            cover(root, l, r, d);
            return;
        }
        pushDown(root, l, r);
        int mid = (l + r) / 2;
        if (right <= mid) {
            modifyAdd(LC, l, mid, left, right, d);
        } else if (left > mid) {
            modifyAdd(RC, mid + 1, r, left, right, d);
        } else {
            modifyAdd(LC, l, mid, left, mid, d);
            modifyAdd(RC, mid + 1, r, mid + 1, right, d);
        }
        pushUp(root);
    }

    long long query(int root, int l, int r, int left, int right) {
        if (l == left && r == right) {
            return sum[root];
        }
        pushDown(root, l, r);
        int mid = (l + r) / 2;
        if (right <= mid) {
            return query(LC, l, mid, left, right);
        } else if (left > mid) {
            return query(RC, mid + 1, r, left, right);
        } else {
            return query(LC, l, mid, left, mid) +
                   query(RC, mid + 1, r, mid + 1, right);
        }
    }
} tree;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    tree.build(1, 1, n);
    char opt;
    for (int i = 1, x, y; i <= m; ++i) {
        scanf("\n%c %d %d", &opt, &x, &y);
        if (opt == 'P') {
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
                tree.modifyAdd(1, 1, n, dfn[top[x]], dfn[x], 1);
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) std::swap(x, y);
            tree.modifyAdd(1, 1, n, dfn[x], dfn[y], 1);
            tree.modifyAdd(1, 1, n, dfn[x], dfn[x], -1);
        } else {
            if (dep[x] < dep[y]) std::swap(x, y);
            printf("%lld\n", tree.query(1, 1, n, dfn[x], dfn[x]));
        }
    }
    return 0;
}
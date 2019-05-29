#include <algorithm>
#include <cstdio>

#define LC (root * 2)
#define RC (root * 2 + 1)

const int MAXN = 100000 + 5;

int n, m;
int weight[MAXN], head[MAXN], to[MAXN * 2], next[MAXN * 2], cnt;
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
            sum[root] = weight[pos[l]];
            tag[root] = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(LC, l, mid);
        build(RC, mid + 1, r);
        pushUp(root);
    }

    void modifyPoint(int root, int l, int r, int p, int d) {
        if (l == r) {
            sum[root] += d;
            return;
        }
        int mid = (l + r) / 2;
        if (p <= mid) {
            modifyPoint(LC, l, mid, p, d);
        } else {
            modifyPoint(RC, mid + 1, r, p, d);
        }
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
        pushUp(root);
    }
} tree;

int main() {
#ifndef ONLINE_JUDGE
    freopen("data/P3178.in", "r", stdin);
    freopen("data/P3178.out", "w", stdout);
#endif
    scanf("%d %d", &n, &m);
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
    tree.build(1, 1, n);
    long long ans = 0;
    for (int i = 1, opt, x, a; i <= m; ++i) {
        scanf("%d %d", &opt, &x);
        switch (opt) {
        case 1:
            scanf("%d", &a);
            tree.modifyPoint(1, 1, n, dfn[x], a);
            break;

        case 2:
            scanf("%d", &a);
            tree.modifyAdd(1, 1, n, dfn[x], dfn[x] + size[x] - 1, a);
            break;

        case 3:
            ans = 0;
            while (x) {
                ans += tree.query(1, 1, n, dfn[top[x]], dfn[x]);
                x = fa[top[x]];
            }
            printf("%lld\n", ans);
            break;
        }
    }
    return 0;
}
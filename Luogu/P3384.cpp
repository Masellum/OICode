#include <algorithm>
#include <cstdio>

#define LC (root * 2)
#define RC (root * 2 + 1)

const int MAXN = 100000 + 5;

int n, m, r, p;
int to[2 * MAXN], head[MAXN], next[2 * MAXN], weight[MAXN], cnt;
int fa[MAXN], dep[MAXN], size[MAXN], son[MAXN], top[MAXN], dfn[MAXN], ind[MAXN],
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
        if (son[u] == -1 || size[v] > size[son[u]]) {
            son[u] = v;
        }
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++ts;
    ind[ts] = u;
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

    void pushUp(int root) { sum[root] = (1ll * sum[LC] + sum[RC]) % p; }

    void build(int root, int l, int r) {
        if (l == r) {
            sum[root] = 1ll * weight[ind[l]] % p;
            tag[root] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(LC, l, mid);
        build(RC, mid + 1, r);
        pushUp(root);
    }

    void cover(int root, int l, int r, int d) {
        sum[root] = (sum[root] + 1ll * (r - l + 1) % p * (d % p) % p) % p;
        tag[root] = (tag[root] + d % p) % p;
    }

    void pushDown(int root, int l, int r) {
        if (tag[root] && l != r) {
            int mid = (l + r) >> 1;
            cover(LC, l, mid, tag[root]);
            cover(RC, mid + 1, r, tag[root]);
            tag[root] = 0;
        }
    }

    void add(int root, int l, int r, int left, int right, int d) {
        if (left <= l && r <= right) {
            cover(root, l, r, d);
            return;
        }
        pushDown(root, l, r);
        int mid = (l + r) >> 1;
        if (right <= mid) {
            add(LC, l, mid, left, right, d);
        } else if (left > mid) {
            add(RC, mid + 1, r, left, right, d);
        } else {
            add(LC, l, mid, left, mid, d);
            add(RC, mid + 1, r, mid + 1, right, d);
        }
        pushUp(root);
    }

    long long query(int root, int l, int r, int left, int right) {
        if (left <= l && r <= right) {
            return sum[root];
        }
        pushDown(root, l, r);
        int mid = (l + r) >> 1;
        if (right <= mid) {
            return query(LC, l, mid, left, right);
        } else if (left > mid) {
            return query(RC, mid + 1, r, left, right);
        } else {
            return (1ll * (query(LC, l, mid, left, mid) % p) +
                    (query(RC, mid + 1, r, mid + 1, right) % p)) %
                   p;
        }
        pushUp(root);
    }
} segT;

int main() {
#ifndef ONLINE_JUDGE
    freopen("data/P3834.in", "r", stdin);
    freopen("data/P3834.out", "w", stdout);
#endif
    scanf("%d %d %d %d", &n, &m, &r, &p);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", weight + i);
    }
    for (int i = 1, x, y; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }
    dfs1(r, 0);
    dfs2(r, r);
    segT.build(1, 1, n);
    long long ans = 0;
    for (int i = 1, opt, x, y, z; i <= m; ++i) {
        scanf("%d%d", &opt, &x);
        switch (opt) {
        case 1:
            scanf("%d%d", &y, &z);
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]])
                    std::swap(x, y);
                segT.add(1, 1, n, dfn[top[x]], dfn[x], z);
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) std::swap(x, y);
            segT.add(1, 1, n, dfn[x], dfn[y], z);
            break;

        case 2:
            scanf("%d", &y);
            ans = 0;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
                ans = (1ll * ans % p + segT.query(1, 1, n, dfn[top[x]], dfn[x]) % p) % p;
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) std::swap(x, y);
            ans = (1ll * ans % p + segT.query(1, 1, n, dfn[x], dfn[y]) % p) % p;
            printf("%lld\n", ans);
            break;

        case 3:
            scanf("%d", &z);
            segT.add(1, 1, n, dfn[x], dfn[x] + size[x] - 1, z);
            break;

        case 4:
            printf("%lld\n", segT.query(1, 1, n, dfn[x], dfn[x] + size[x] - 1) % p);
            break;
        }
    }
    return 0;
}
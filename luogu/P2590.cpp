#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

#define LC root * 2
#define RC root * 2 + 1

#define FUCK(x) printf("Fuck "#x)

const int MAXN = 30000 + 5;

int n, q, to[2 * MAXN], next[2 * MAXN], head[MAXN], cnt;
int weight[MAXN], fa[MAXN], dep[MAXN], size[MAXN], son[MAXN], dfn[MAXN],
    pos[MAXN], top[MAXN], ts;

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
    long long sum[4 * MAXN];
    int max[4 * MAXN];

    void pushUp(int root) {
        sum[root] = sum[LC] + sum[RC];
        max[root] = std::max(max[LC], max[RC]);
    }

    void build(int root, int l, int r) {
        if (l == r) {
            sum[root] = max[root] = weight[pos[l]];
            return;
        }
        int mid = (l + r) / 2;
        build(LC, l, mid);
        build(RC, mid + 1, r);
        pushUp(root);
    }

    void modify(int root, int l, int r, int x, int d) {
        if (l == r) {
            sum[root] = max[root] = d;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid)
            modify(LC, l, mid, x, d);
        else
            modify(RC, mid + 1, r, x, d);
        pushUp(root);
    }

    long long querySum(int root, int l, int r, int left, int right) {
        if (l == left && r == right) {
            return sum[root];
        }
        int mid = (l + r) / 2;
        if (right <= mid) {
            return querySum(LC, l, mid, left, right);
        } else if (left > mid) {
            return querySum(RC, mid + 1, r, left, right);
        } else {
            return 1ll * querySum(LC, l, mid, left, mid) + querySum(RC, mid + 1, r, mid + 1, right);
        }
    }

    int queryMax(int root, int l, int r, int left, int right) {
        if (l == left && r == right) {
            return max[root];
        }
        int mid = (l + r) / 2;
        if (right <= mid) {
            return queryMax(LC, l, mid, left, right);
        } else if (left > mid) {
            return queryMax(RC, mid + 1, r, left, right);
        } else {
            return std::max(queryMax(LC, l, mid, left, mid), queryMax(RC, mid + 1, r, mid + 1, right));
        }
    }
} tree;

int main() {
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", weight + i);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    tree.build(1, 1, n);
    scanf("%d", &q);
    for (int i = 1, u, v; i <= q; ++i) {
        char opt[8];
        scanf("%s%d%d", opt, &u, &v);
        long long ans;
        if (opt[0] == 'C') {
            tree.modify(1, 1, n, dfn[u], v);
        } else if (opt[1] == 'S') {
            ans = 0;
            while (top[u] != top[v]) {
                if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
                ans += tree.querySum(1, 1, n, dfn[top[u]], dfn[u]);
                u = fa[top[u]];
            }
            if (dep[u] > dep[v]) std::swap(u, v);
            ans += tree.querySum(1, 1, n, dfn[u], dfn[v]);
            printf("%lld\n", ans);
        } else {
            ans = LLONG_MIN;
            while (top[u] != top[v]) {
                if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
                ans = std::max(ans, 1ll * tree.queryMax(1, 1, n, dfn[top[u]], dfn[u]));
                u = fa[top[u]];
            }
            if (dep[u] > dep[v]) std::swap(u, v);
            ans = std::max(ans, 1ll * tree.queryMax(1, 1, n, dfn[u], dfn[v]));
            printf("%lld\n", ans);
        }
    }
    return 0;
}
#include <algorithm>
#include <cstdio>

#define LC (root * 2)
#define RC (root * 2 + 1)

const int MAXN = 100000 + 5;

int n, q;
int head[MAXN], to[MAXN * 2], next[MAXN * 2], cnt;
int fa[MAXN], dep[MAXN], size[MAXN], son[MAXN], dfn[MAXN], top[MAXN], ts;

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
        if (son[u] == -1 || size[son[u]] < size[v]) {
            son[u] = v;
        }
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++ts;
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
    int sum[MAXN * 4], tag[MAXN * 4];

    void pushUp(int root) { sum[root] = sum[LC] + sum[RC]; }

    void build(int root, int l, int r) {
        if (l == r) {
            sum[root] = 0;
            tag[root] = -1;
            return;
        }
        int mid = (l + r) / 2;
        build(LC, l, mid);
        build(RC, mid + 1, r);
        tag[root] = -1;
        pushUp(root);
    }

    void cover(int root, int l, int r, int x) {
        sum[root] = (r - l + 1) * x;
        tag[root] = x;
    }

    void pushDown(int root, int l, int r) {
        if (tag[root] != -1 && l != r) {
            int mid = (l + r) / 2;
            cover(LC, l, mid, tag[root]);
            cover(RC, mid + 1, r, tag[root]);
            tag[root] = -1;
        }
    }

    void modifyInterval(int root, int l, int r, int left, int right, int x) {
        if (l == left && r == right) {
            cover(root, l, r, x);
            return;
        }
        pushDown(root, l, r);
        int mid = (l + r) / 2;
        if (right <= mid) {
            modifyInterval(LC, l, mid, left, right, x);
        } else if (left > mid) {
            modifyInterval(RC, mid + 1, r, left, right, x);
        } else {
            modifyInterval(LC, l, mid, left, mid, x);
            modifyInterval(RC, mid + 1, r, mid + 1, right, x);
        }
        pushUp(root);
    }

    int querySum(int root, int l, int r, int left, int right) {
        if (l == left && r == right) {
            return sum[root];
        }
        pushDown(root, l, r);
        int mid = (l + r) / 2;
        if (right <= mid) {
            return querySum(LC, l, mid, left, right);
        } else if (left > mid) {
            return querySum(RC, mid + 1, r, left, right);
        } else {
            return querySum(LC, l, mid, left, mid) +
                   querySum(RC, mid + 1, r, mid + 1, right);
        }
    }
} tree;

int main() {
    scanf("%d", &n);
    for (int i = 1, u; i < n; ++i) {
        scanf("%d", &u);
        addEdge(i + 1, u + 1);
        addEdge(u + 1, i + 1);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    tree.build(1, 1, n);
    scanf("%d", &q);
    char opt[10];
    for (int i = 1, x, formerSum; i <= q; ++i) {
        scanf("%s%d", opt, &x);
        ++x;
        if (opt[0] == 'i') {
            formerSum = tree.querySum(1, 1, n, 1, n);
            do {
                tree.modifyInterval(1, 1, n, dfn[top[x]], dfn[x], 1);
                x = fa[top[x]];
            } while (x != 0);
            printf("%d\n", tree.querySum(1, 1, n, 1, n) - formerSum);
        } else {
            formerSum = tree.querySum(1, 1, n, dfn[x], dfn[x] + size[x] - 1);
            tree.modifyInterval(1, 1, n, dfn[x], dfn[x] + size[x] - 1, 0);
            printf("%d\n", formerSum);
        }
    }
    return 0;
}
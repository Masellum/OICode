#include <algorithm>
#include <cstdio>

#define LC (root * 2)
#define RC (root * 2 + 1)

const int MAXN = 100000 + 5;

int n, m;
int head[MAXN], to[2 * MAXN], next[2 * MAXN], cnt;
int color[MAXN], fa[MAXN], dep[MAXN], size[MAXN], son[MAXN], top[MAXN], dfn[MAXN], pos[MAXN], ts;

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
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
            return;
        dfs2(v, v);
    }
}

struct SegmentTree {
    int count[4 * MAXN], leftColor[4 * MAXN], rightColor[4 * MAXN], tag[4 * MAXN];

    void pushUp(int root) {
        count[root] = count[LC] + count[RC];
        if (rightColor[LC] == leftColor[RC])
            count[root]--;
    }

    void build(int root, int l, int r) {
        if (l == r) {
            count[root] = 1;
            leftColor[root] = rightColor[root] = color[pos[l]];
            tag[root] = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(LC, l, mid);
        build(RC, mid + 1, r);
        leftColor[root] = leftColor[LC];
        rightColor[root] = rightColor[RC];
        pushUp(root);
    }

    void cover(int root, int c) {
        count[root] = 1;
        leftColor[root] = rightColor[root] = c;
        tag[root] = c;
    }

    void pushDown(int root, int l, int r) {
        if (tag[root] && l != r) {
            cover(LC, tag[root]);
            cover(RC, tag[root]);
            tag[root] = 0;
        }
    }

    void intervalModify(int root, int l, int r, int left, int right, int c) {
        if (l == left && r == right) {
            cover(root, c);
            return;
        }
        pushDown(root, l, r);
        int mid = (l + r) / 2;
        if (right <= mid) {
            intervalModify(LC, l, mid, left, right, c);
        } else if (left > mid) {
            intervalModify(RC, mid + 1, r, left, right, c);
        } else {
            intervalModify(LC, l, mid, left, mid, c);
            intervalModify(RC, mid + 1, r, mid + 1, right, c);
        }
        pushUp(root);
    }

    int intervalQuery(int root, int l, int r, int left, int right) {
        if (l == left && r == right) {
            return count[root];
        }
        pushDown(root, l, r);
        int mid = (l + r) / 2, ans;
        if (right <= mid) {
            return intervalQuery(LC, l, mid, left, right);
        } else if (left > mid) {
            return intervalQuery(RC, mid + 1, r, left, right);
        } else {
            ans = intervalQuery(LC, l, mid, left, mid) + intervalQuery(RC, mid + 1, r, mid + 1, right);
            if (rightColor[LC] == leftColor[RC]) ans--;
            return ans;
        }
    }
} tree;

void modify(int u, int v, int c) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        tree.intervalModify(1, 1, n, dfn[top[u]], dfn[u], c);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) std::swap(u, v);
    tree.intervalModify(1, 1, n, dfn[u], dfn[v], c);
}

int query(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        res += tree.intervalQuery(1, 1, n, dfn[top[u]], dfn[u]);
        if (color[fa[top[u]]] == color[top[u]]) res--;
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) std::swap(u, v);
    res += tree.intervalQuery(1, 1, n, dfn[u], dfn[v]);
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", color + i);
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    tree.build(1, 1, n);
    char opt;
    for (int i = 1, a, b, c; i <= m; ++i) {
        scanf("\n%c %d %d", &opt, &a, &b);
        if (opt == 'C') {
            scanf("%d", &c);
            modify(a, b, c);
        } else {
            printf("%d\n", query(a, b));
        }
    }
    return 0;
}
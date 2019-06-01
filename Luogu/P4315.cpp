#include <algorithm>
#include <cstdio>

#define LC (root * 2)
#define RC (root * 2 + 1)

const int MAXN = 100000 + 5;

int n;
int head[MAXN], to[MAXN * 2], next[MAXN * 2], edgeWeight[MAXN * 2], cnt;
int vertexWeight[MAXN], fa[MAXN], dep[MAXN], size[MAXN], son[MAXN], top[MAXN], dfn[MAXN], pos[MAXN], ts;

void addEdge(int f, int t, int w) {
    to[++cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
    edgeWeight[cnt] = w;
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
        vertexWeight[v] = edgeWeight[e];
        size[u] += size[v];
        if (son[u] == -1 || size[son[u]] < size[v]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++ts;
    pos[ts] = u;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}

struct SegmentTree {
    int max[MAXN * 4];
    long long tagAdd[MAXN * 4], tagCover[MAXN * 4];

    void pushUp(int root) {
        max[root] = std::max(max[LC], max[RC]);
    }

    void build(int root, int l, int r) {
        if (l == r) {
            max[root] = vertexWeight[pos[l]];
            tagAdd[root] = 0;
            tagCover[root] = -1;
            return;
        }
        int mid = (l + r) / 2;
        build(LC, l, mid);
        build(RC, mid + 1, r);
        pushUp(root);
    }

    void add(int root, int l, int r, int d) {
        max[root] += d;
        tagAdd[root] += d;
    }

    void cover(int root, int l, int r, int x) {
        max[root] = x;
        tagCover[root] = x;
        tagAdd[root] = 0;
    }

    void pushDown(int root, int l, int r) {
        int mid = (l + r) / 2;
        if (tagCover[root] != -1) {
            cover(LC, l, mid, tagCover[root]);
            cover(RC, mid + 1, r, tagCover[root]);
            tagCover[root] = -1;
        }
        if (tagAdd[root]) {
            add(LC, l, mid, tagAdd[root]);
            add(RC, mid + 1, r, tagAdd[root]);
            tagAdd[root] = 0;
        }
    }

    void modifyCover(int root, int l, int r, int left, int right, int x) {
        if (l == left && r == right) {
            cover(root, l, r, x);
        }
        pushDown(root, l, r);
        int mid = (l + r) / 2;
        if (right <= mid) {
            modifyCover(LC, l, mid, left, right, x);
        } else if (left > mid) {
            modifyCover(RC, mid + 1, r, left, right, x);
        } else {
            modifyCover(LC, l, mid, left, mid, x);
            modifyCover(RC, mid + 1, r, mid + 1, right, x);
        }
        pushUp(root);
    }

    void modifyAdd(int root, int l, int r, int left, int right, int d) {
        if (l == left && ri == right) {
            add(root, l, r, d);
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

    long long queryMax(int root, int l, int r, int left, int right) {
        if (l == left && r == right) {
            return max[root];
        }
        pushDown(root);
        int mid = (l + r) / 2;
        if (right <= mid) {
            queryMax(LC, l, mid, left, right);
        } else if (left > mid) {
            queryMax(RC, mid + 1, r, left, right);
        } else {
            queryMax(LC, l, mid, left, mid);
            queryMax(RC, mid + 1, r, mid + 1, right);
        }
    }
} tree;

int main() {
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    tree.build(1, 1, n);
    char opt[7];
    scanf("%s", opt);
    int u, v, w;
    while (opt[0] != S) {
        scanf("%d %d", &u, &v);
        if (opt[0] == 'C') {
            if (opt[1] == 'h') {

            } else {

            }
        } else if (opt[0] == 'A') {

        } else {

        }
    }
}
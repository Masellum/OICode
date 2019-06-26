#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>

#define LC (root * 2)
#define RC (root * 2 + 1)

const int MAXN = 200000 + 5;

int n, m;
int head[MAXN], to[2 * MAXN], next[2 * MAXN], edgeWeight[2 * MAXN], cnt;
int vertexWeight[MAXN], fath[MAXN], dep[MAXN], size[MAXN], son[MAXN], top[MAXN],
    dfn[MAXN], pos[MAXN], ts;
long long ans0;

struct Edge {
    int from, to, weight, num;
    bool inMST;

    Edge() {}
    Edge(int from, int to, int weight, int num) : from(from), to(to), weight(weight), num(num), inMST(false) {}

} graphEdge[MAXN], *tail = graphEdge + 1;

inline void addGraphEdge(int u, int v, int w, int num) {
    tail->from = u;
    tail->to = v;
    tail->weight = w;
    tail->num = num;
    *tail++ = Edge(u, v, w, num);
}

inline void addEdge(int u, int v, int w) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
    edgeWeight[cnt] = w;
}

// struct Edge {
//     int from, to, weight, num;
//     Edge() {}
//     Edge(int from, int to, int weight, int num) : from(from)
// }

// struct DisjointSet {
    int fa[MAXN], rank[MAXN];

    // DisjointSet() {}

    // DisjointSet(int n) {
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return;
        if (rank[x] > rank[y])
            std::swap(x, y);
        if (rank[x] < rank[y] || rand() % 2) {
            fa[x] = y;
            rank[y]++;
        } else {
            fa[y] = x;
            rank[x]++;
        }
    }
// } ds;

// void kruskal(DisjointSet &ds) {
void kruskal() {
    // DisjointSet ds(m);
    init(n);
    std::sort(graphEdge + 1, graphEdge + m + 1, [](const Edge &a, const Edge &b) -> bool {
        return a.weight < b.weight;
    });
    for (int i = 1, u, v, w; i <= m; ++i) {
        u = graphEdge[i].from, v = graphEdge[i].to, w = graphEdge[i].weight;
        // if (ds.find(u) != ds.find(v)) {
            // ds.merge(u, v);
        if (find(u) != find(v)) {
            merge(u, v);
            addEdge(u, v, w);
            addEdge(v, u, w);
            ans0 += w;
            graphEdge[i].inMST = true;
        }
    }
    std::sort(graphEdge + 1, graphEdge + m + 1, [](const Edge &a, const Edge &b) -> bool {
        return a.num < b.num;
    });
}

void dfs1(int u, int f) {
    fath[u] = f;
    dep[u] = dep[fath[u]] + 1;
    size[u] = 1;
    son[u] = -1;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == f)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        vertexWeight[v] = edgeWeight[e];
        if (son[u] == -1 || size[v] > size[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++ts;
    pos[ts] = u;
    if (son[u] == -1)
        return;
    dfs2(son[u], t);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fath[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}

struct SegmentTree {
    int max[4 * MAXN];

    void pushUp(int root) {
        max[root] = std::max(max[LC], max[RC]);
    }

    void build(int root, int l, int r) {
        if (l == r) {
            max[root] = vertexWeight[pos[l]];
            return;
        }
        int mid = (l + r) / 2;
        build(LC, l, mid);
        build(RC, mid + 1, r);
        pushUp(root);
    }

    int query(int root, int l, int r, int left, int right) {
        if (l == r) {
            return max[root];
        }
        int mid = (l + r) / 2;
        if (right <= mid) {
            return query(LC, l, mid, left, right);
        } else if (left > mid) {
            return query(RC, mid + 1, r, left, right);
        } else {
            return std::max(query(LC, l, mid, left, mid), query(RC, mid + 1, r, mid + 1, right));
        }
    }
} tree;

int query(int u, int v) {
    int res = INT_MIN;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            std::swap(u, v);
        res = std::max(res, tree.query(1, 1, n, dfn[top[u]], dfn[u]));
        u = fath[top[u]];
    }
    if (dep[u] > dep[v])
        std::swap(u, v);
    if (dfn[u] < dfn[v]) {
        res = std::max(res, tree.query(1, 1, n, dfn[u] + 1, dfn[v]));
    }
    return res;
}

int main() {
    srand(time(NULL));
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v, w; i <= m; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addGraphEdge(u, v, w, i);
    }
    // ds = DisjointSet(m);
    // kruskal(ds);
    kruskal();
    dfs1(1, 0);
    dfs2(1, 1);
    tree.build(1, 1, n);
    long long res = LLONG_MIN;
    for (int i = 1, u, v, w; i <= m; ++i) {
        res = LLONG_MIN;
        u = graphEdge[i].from, v = graphEdge[i].to, w = graphEdge[i].weight;
        if (graphEdge[i].inMST)
            res = ans0;
        else
            res = std::max(res, ans0 + w - query(u, v));
        printf("%lld\n", res);
    }
    return 0;
}
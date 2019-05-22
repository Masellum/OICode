#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MAXN = 5000 + 5, MAXM = 200000 + 5;

int n, m, cnt, ans;

struct DisjointSet {
    int fa[MAXN], rank[MAXN];

    void init() {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
        }
    }

    int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (rank[x] > rank[y])
            std::swap(x, y);
        if (rank[x] < rank[y]) {
            fa[x] = y;
        } else {
            if (rand() % 2 > 1) {
                fa[x] = y;
                rank[y]++;
            } else {
                fa[y] = x;
                rank[x]++;
            }
        }
    }
} ds;

struct Edge;

Edge *head[MAXN];

struct Edge {
    int from, to;
    int weight;
    Edge *next;

    Edge() {}
    Edge(int f, int t, int w) : from(f), to(t), weight(w), next(head[f]) {}
} edge[MAXM];

void addEdge(int from, int to, int weight) {
    head[from] = new Edge(from, to, weight);
    head[to] = new Edge(to, from, weight);
    edge[++cnt] = *head[from];
}

void kruskal() {
    DisjointSet ds;
    ds.init();
    std::sort(edge + 1, edge + m + 1, [](const Edge &a, const Edge &b) -> bool {
        return a.weight < b.weight;
    });
    for (int i = 1; i <= m; ++i) {
        if (ds.find(edge[i].from) != ds.find(edge[i].to)) {
            ds.merge(edge[i].from, edge[i].to);
            ans += edge[i].weight;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    int x, y, z;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        addEdge(x, y, z);
    }
    kruskal();
    printf("%d", ans);
    return 0;
}
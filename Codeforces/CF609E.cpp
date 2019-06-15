#include <algorithm>
#include <ctime>
#include <cstdio>
#include <cstdlib>

const int MAXN = 200000 + 5;

int n, m;
int head[MAXN], to[2 * MAXN], next[2 * MAXN], edgeWeight[2 * MAXN], cnt;
int vertexWeight[MAXN], fa[MAXN], dep[MAXN], size[MAXN], son[MAXN], top[MAXN], dfn[MAXN], pos[MAXN], ts;

struct Edge;
Edge *graphHead[MAXN];

struct Edge {
    int from, to, weight;
    Edge *next;

    Edge() {}
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight), next(graphHead[from]) {}
} graphEdge[MAXN];

void addEdge(int u, int v, int w) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
    edgeWeight[cnt] = w;
}

struct DisjointSet {
    int fa[MAXN], rank[MAXN];

    DisjointSet(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x) {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (rank[x] > rank[y]) std::swap(x, y);
        if (rank[x] < rank[y] || rand() % 2) {
            fa[x] = y;
            rank[y]++;
        } else {
            fa[y] = x;
            rank[x]++;
        }
    }
};

void kruskal() {

}
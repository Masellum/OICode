#include <algorithm>
#include <cstdio>
#include <climits>
#include <vector>

const int MAXN = 500000 + 5;

int n, c[MAXN], size[MAXN], f[MAXN];
struct Edge {
    int size, f, to;

    Edge() {}
    Edge(int to) : size(1), f(c[to]), to(to) {}
    
    bool operator<(const Edge &that) {
        return f - 2 * size > that.f - 2 * that.size;
    }
};

std::vector<Edge> edge[MAXN];

void addEdge(int u, int v) {
    edge[u].push_back(Edge(v));
    edge[v].push_back(Edge(u));
}

void dfs(int fa, int u) {
    size[u] = 1;
    f[u] = u == 1 ? 0 : c[u];
    for (int i = 0, v; i < int(edge[u].size()); ++i) {
        Edge &e = edge[u][i];
        v = e.to;
        if (v == fa) continue;
        dfs(u, v);
        e.size = size[v];
        e.f = f[v];
    }
    std::sort(edge[u].begin(), edge[u].end());
    for (int i = 0, v; i < int(edge[u].size()); ++i) {
        Edge &e = edge[u][i];
        v = e.to;
        if (v == fa) continue;
        f[u] = std::max(f[u], 2 * (size[u] - 1) + f[v] + 1);
        size[u] += size[v];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    dfs(0, 1);
    printf("%d", std::max(f[1], 2 * n - 2 + c[1]));
    return 0;
}
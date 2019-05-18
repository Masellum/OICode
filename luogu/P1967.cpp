#include <cmath>
#include <ctime>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <algorithm>

const int MAXN = 10000 + 5, MAXM = 50000 + 5;

int n, m, q, ans;

struct DisjointSet {
    int fa[MAXN], rank[MAXN];

    int find(int x) {
        return x == fa[x] ? x : (fa[x] = find(fa[x]));
    }

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

    DisjointSet(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
        }
    }
};

struct Edge;

Edge *head[MAXN], *hmst[MAXN];
int cnt;

struct Edge {
    int from, to, weight;
    Edge *next;

    Edge() {}
    Edge(int f, int t, int w) : from(f), to(t), weight(w), next(head[f]) {}
    Edge(int f, int t, int w, int flag) : from(f), to(t), weight(w), next(hmst[f]) {}
} edge[MAXM];

void addEdge(int f, int t, int w) {
    head[f] = new Edge(f, t, w);
    head[t] = new Edge(t, f, w);
    edge[++cnt] = *head[f];
}
void addMSTEdge(int f, int t, int w) {
    hmst[f] = new Edge(f, t, w, 0);
    hmst[t] = new Edge(t, f, w, 0);
}

void kruskal() {
    std::sort(edge + 1, edge + m + 1, [](const Edge &a, const Edge &b) -> bool {
       return a.weight > b.weight;
    });
    cnt = 0;
    DisjointSet ds(n);
    for (int i = 1; i <= m; ++i) {
        if (cnt == 2 * n - 2)
            return;
        if (ds.find(edge[i].from) != ds.find(edge[i].to))
        {
            ds.merge(edge[i].from, edge[i].to);
            addMSTEdge(edge[i].from, edge[i].to, edge[i].weight);
            cnt++;
        }
    }
}

bool vis[MAXN];
int f[MAXN][15], dep[MAXN], log_2[MAXN], faw[MAXN];

void initlog() {
    for (int i = 1; i <= n; ++i) {
        log_2[i] = (log_2[i - 1]) + (1 << log_2[i - 1] == i);
    }
}

void dfs(int x, int fa) {
    vis[x] = true;
    f[x][0] = fa;
    dep[x] = dep[fa] + 1;
    for (int j = 1; (1 << j) <= dep[x]; ++j) {
        f[x][j] = f[f[x][j - 1]][j - 1];
    }
    for (Edge *e = hmst[x]; e; e = e->next) {
        if (!vis[e->to]) {
            dfs(e->to, x);
            faw[e->to] = e->weight;
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        std::swap(x, y);
    while (dep[x] > dep[y]) {
        x = f[x][log_2[dep[x] - dep[y]] - 1];
    }
    if (x == y)
        return x;
    for (int j = log_2[dep[x]]; j >= 0; --j) {
        if (f[x][j] == f[y][j])
            continue;
        x = f[x][j];
        y = f[y][j];
    }
    return f[x][0];
}

int main() {
    scanf("%d %d", &n, &m);
    int x, y, z;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        addEdge(x, y, z);
    }
    kruskal();
    initlog();
    for (int i = 1; i <= n; ++i) {
        if (!vis[i])
            dfs(i, 0);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        ans = INT_MAX;
        scanf("%d %d", &x, &y);
        z = lca(x, y);
        if (z != 0) {
            while (x != z) {
                ans = std::min(ans, faw[x]);
                x = f[x][0];
            }
            while (y != z) {
                ans = std::min(ans, faw[y]);
                y = f[y][0];
            }
            printf("%d\n", ans);
        } else {
            puts("-1");
        }
    }
    return 0;
}
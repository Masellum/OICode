#include <algorithm>
#include <cstdio>
#include <vector>

const int MAXN = 500000 + 1;

std::vector<int> edge[MAXN];

int n, m;
// int to[MAXN * 2], head[MAXN], next[MAXN * 2], cnt;
int fa[MAXN], top[MAXN], son[MAXN], size[MAXN], dep[MAXN];

// void addEdge(int u, int v) {
//     to[++cnt] = v;
//     next[cnt] = head[u];
//     head[u] = cnt;
// }

void addEdge(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    size[u] = 1;
    son[u] = -1;
    // for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
    for (auto it = edge[u].begin(); it != edge[u].end(); it++) {
        int v = *it;
        if (v == fa[u]) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (son[u] == -1 || size[v] > size[son[u]]) {
            son[u] = v;
        }
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (auto it = edge[u].begin(); it != edge[u].end(); ++it) {
        int v = *it;
    // for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int getLCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) y = fa[top[y]];
        else x = fa[top[x]];
    }
    return (dep[x] < dep[y] ? x : y);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1, a, b, c, x, y, z; i <= m; ++i) {
        scanf("%d %d %d", &a, &b, &c);
        x = getLCA(a, b), y = getLCA(b, c), z = getLCA(a, c);
        printf("%d", std::max({x, y, z}, [](const int &x, const int &y) -> bool {
            return dep[x] < dep[y];
        })); // c++11
        // if (dep[x] > dep[y]) std::swap(x, y);
        // if (dep[y] > dep[z]) std::swap(y, z);
        printf(" %d\n", dep[a] + dep[b] + dep[c] - dep[x] - dep[y] - dep[z]);
    }
    return 0;
}
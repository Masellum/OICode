#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 1000 + 5;

int n, m, e;
int head[MAXN], to[MAXN * MAXN], next[MAXN * MAXN], cnt;
int f[MAXN], ans;
bool vis[MAXN];

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

bool dfs(int u) {
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (vis[v]) continue;
        vis[v] = true;
        if (!f[v] || dfs(v)) {
            f[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d %d %d", &n, &m, &e);
    for (int i = 1, u, v; i <= e; ++i) {
        scanf("%d %d", &u, &v);
        if (u <= n && v <= m) addEdge(u, v + n);
    }
    for (int i = 1; i <= n; ++i) {
        memset(f, 0, sizeof(f));
        if (dfs(i)) ans++;
    }
    printf("%d", ans);
    return 0;
}
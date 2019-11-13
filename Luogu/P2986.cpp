#include <algorithm>
#include <cstdio>

const int MAXN = 100000 + 5;

int n;
int c[MAXN], head[MAXN], to[2 * MAXN], next[2 * MAXN], len[2 * MAXN], ecnt;
int tot, cnt[MAXN];
long long f[MAXN], g[MAXN], ans = (1ll << 62);

void addEdge(int u, int v, int w) {
    to[++ecnt] = v;
    len[ecnt] = w;
    next[ecnt] = head[u];
    head[u] = ecnt;
}

void dfs1(int u, int fa) {
    tot += (cnt[u] = c[u]);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa) continue;
        dfs1(v, u);
        f[u] += f[v] + 1ll * cnt[v] * len[e];
        cnt[u] += cnt[v];
    }
}

void dfs2(int u, int fa) {
    ans = std::min(ans, g[u]);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa) continue;
        g[v] = g[u] + 1ll * (tot - 2 * cnt[v]) * len[e];
        dfs2(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
    }
    for (int i = 1, u, v, w; i < n; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dfs1(1, 0);
    g[1] = f[1];
    dfs2(1, 0);
    printf("%lld", ans);
    return 0;
}
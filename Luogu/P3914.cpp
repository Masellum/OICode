#include <algorithm>
#include <cstdio>

const int MAXN = 5000 + 5, MOD = int(1e9 + 7);

int n, m;
int head[MAXN], to[2 * MAXN], next[2 * MAXN], cnt;
int f[MAXN][MAXN], k[MAXN], total[MAXN];

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int fa, int u) {
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa)
            continue;
        dfs(u, v);
    }
    for (int i = 1; i <= m; ++i) {
        if (f[u][i]) {
            for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
                if (v == fa) continue;
                f[u][i] = 1ll * f[u][i] * ((((total[v] - f[v][i]) % MOD) + MOD) % MOD) % MOD;
            }
            total[u] = (1ll * total[u] + f[u][i]) % MOD;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &k[i]);
        for (int j = 1, l; j <= k[i]; ++j) {
            scanf("%d", &l);
            f[i][l] = 1;
        }
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(0, 1);
    printf("%d", total[1]);
    return 0;
}
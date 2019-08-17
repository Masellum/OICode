#include <algorithm>
#include <climits>
#include <cstdio>

const int MAXN = 300000 + 5, INF = 0x3f3f3f3f;

int n, m, k;
int head[MAXN], to[MAXN * 2], next[MAXN * 2], cnt;
int f[MAXN], g[MAXN], count;
bool sig[MAXN];

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int mid, int fa, int u) {
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa) continue;
        dfs(mid, u, v);
        f[u] = std::min(f[u], f[v] + 1);
        g[u] = std::max(g[u], g[v] + 1);
    }
    if (sig[u] && f[u] > mid) {
        g[u] = std::max(g[u], 0);
    }
    if (f[u] + g[u] <= mid) {
        g[u] = -INF;
    }
    if (g[u] == mid) {
        count++;
        f[u] = 0;
        g[u] = -INF;
    }
}

bool judge(int mid) {
    std::fill(f + 1, f + n + 1, INF);
    std::fill(g + 1, g + n + 1, -INF);
    count = 0;
    dfs(mid, 0, 1);
    if (g[1] >= 0)
        count++;
    return count <= m;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, d; i <= n; ++i) {
        scanf("%d", &d);
        sig[i] = d;
    }
    for (int i = 1, a, b; i < n; ++i) {
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    int l = 0, r = n, mid = (l + r) / 2, ans;
    while (l <= r) {
        if (judge(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
        mid = (l + r) / 2;
    }
    printf("%d", ans);
    return 0;
}
#include <algorithm>
#include <climits>
#include <cstdio>

const int MAXM = 100000 + 5;

int head[MAXM], to[2 * MAXM], next[2 * MAXM], cnt;
int m, k, p, d[MAXM], count[MAXM], maxd = 2;

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int fa, int u) {
    d[u] = d[fa] + 1;
    count[d[u]]++;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == fa) continue;
        dfs(u, v);
    }
}

int main() {
    scanf("%d %d %d", &m, &k, &p);
    for (int i = 1, u, v; i < m; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(0, 1);
    std::sort(d + 1, d + m + 1);
    int l = 2, r = 2, ans = 1, cost = 0;
    while (l < m && r < m) {
        r++;
        if (d[r] != d[r - 1]) {
            cost += r - l;
        }
        while (cost > p) {
            cost -= d[r] - d[l];
            ++l;
        }
        ans = std::max(ans, r - l + 1);
    }
    ans = std::min(ans, k);
    printf("%d", ans);
    return 0;
}
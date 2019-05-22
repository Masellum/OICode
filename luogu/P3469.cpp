#include <algorithm>
#include <cstdio>
#include <vector>

const int MAXN = 100000 + 5;

int n, m;
int to[MAXN * 2], next[MAXN * 2], head[MAXN], cnt;
int size[MAXN], dfn[MAXN], low[MAXN], ts;
bool isCut[MAXN];
std::vector<int> counts[MAXN];

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

void tarjan(int u, int f) {
    dfn[u] = low[u] = ++ts;
    size[u] = 1;
    int child = 0;
    long long tmp = 0;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == f) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            size[u] += size[v];
            low[u] = std::min(low[u], low[v]);
            // tmp += size[v];
            if (low[v] >= dfn[u]) {
                tmp += size[v];
                isCut[u] = true;
                counts[u].push_back(size[v]);
            }
            // if (low[v] >= dfn[u] && u != f) {
            //     isCut[u] = true;
            //     counts[u].push_back(size[v]);
            // }
            // if (u == f) {
            //     counts[u].push_back(size[v]);
            //     child++;
            // }
        } else if (dfn[v] < dfn[u]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    // if (u == f && child > 1) {
    //     isCut[u] = true;
    // }
    if (isCut[u] && n - tmp - 1 != 0) {
        counts[u].push_back(n - tmp - 1);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen("data/PP3469.in", "r", stdin);
    freopen("data/P3469.out", "w", stdout);
#endif
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    // tarjan(1, 1);
    tarjan(1, 0);
    // for (int i = 1; i <= n; ++i) {
    //         if (isCut[i]) printf("T ");
    //         else printf("F ");
    //     for (auto it = counts[i].begin(); it != counts[i].end(); it++) {
    //         printf("%d ", *it);
    //     }
    //     puts("");
    // }
    for (int i = 1; i <= n; ++i) {
        long long ans = 2 * (n - 1);
        if (isCut[i]) {
            for (auto it = counts[i].begin(); it != counts[i].end(); it++) {
                ans += 1ll * (*it) * (n - *it - 1);
                // for (auto it_ = it + 1; it_ != counts[i].end(); it_++) {
                //     ans += 2 * (*it) * (*it_);
                // }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
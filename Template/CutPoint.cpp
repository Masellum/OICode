#include <cstdio>
#include <algorithm>
#include <vector>

const int MAXN = 20000 + 5, MAXM = 200000 + 5;

int n, m, ts;
int dfn[MAXN], low[MAXN];
int head[MAXN], from[MAXM], to[MAXN], next[MAXN], ecnt;
bool isCut[MAXN];

void addEdge(int f, int t) {
    from[++ecnt] = f;
    to[ecnt] = t;
    next[ecnt] = head[f];
    head[f] = ecnt;
}

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++ts;
    int child = 0;
    for (int e = head[u]; e; e = next[e]) {
        int v = to[e];
        if (v == fa) {
            continue;
        }
        if (!dfn[v]) {
            dfs(v, u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != fa) {
                isCut[u] = true;
            }
            if (u == fa) {
                child++;
            }
        } else if (dfn[v] < dfn[u]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (u == fa && child > 1) {
        isCut[u] = true;
    }
}

std::vector<int> ans;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, x, y; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        addEdge(x, y);
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            dfs(i, i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (isCut[i]) {
            ans.push_back(i);
        }
    }
    printf("%d\n", int(ans.size()));
    for (int i = 0; i < ans.size(); ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <climits>
#include <cstring>
#include <numeric>
#include <stack>
#include <queue>

const int MAXN = 10000 + 5, MAXM = 100000 + 5;

int n, m;
int head[MAXN], from[MAXM], to[MAXM], next[MAXM], weight[MAXN], cnt;
int dfn[MAXN], low[MAXN], ts;
int con[MAXN], ccnt;
bool inStack[MAXN];
bool added[MAXN];
std::stack<int> st;

int shead[MAXN], sfrom[MAXM], sto[MAXM], snext[MAXM], sweight[MAXN], scnt;
int sind[MAXN], dis[MAXN], ans = INT_MIN;

void addEdge(int f, int t) {
    from[++cnt] = f;
    to[cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
}

void addSEdge(int f, int t) {
    sfrom[++scnt] = f;
    sto[scnt] = t;
    snext[scnt] = shead[f];
    shead[f] = scnt;
    sind[t]++;
}

void dfs(int u) {
    low[u] = dfn[u] = ++ts;
    inStack[u] = true;
    st.push(u);
    for (int e = head[u]; e; e = next[e]) {
        int v = to[e];
        if (!dfn[v]) {
            dfs(v);
            low[u] = std::min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    int t;
    if (dfn[u] == low[u]) {
        ccnt++;
        while ((t = st.top())) {
            inStack[t] = false;
            con[t] = ccnt;
            st.pop();
            if (t == u) {
                break;
            }
        }
    }
}

void topo() {
    std::fill(dis + 1, dis + ccnt + 1, INT_MIN);
    std::queue<int> q;
    for (int i = 1; i <= ccnt; ++i) {
        if (!sind[i]) {
            q.push(i);
            dis[i] = sweight[i];
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int e = shead[u]; e; e = snext[e]) {
            int v = sto[e];
            dis[v] = std::max(dis[v], dis[u] + sweight[v]);
            sind[v]--;
            if (sind[v] == 0) {
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= ccnt; ++i) {
        ans = std::max(ans, dis[i]);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", weight + i);
    }
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            dfs(i);
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (con[from[i]] != con[to[i]]) {
            addSEdge(con[from[i]], con[to[i]]);
        }
        if (!added[from[i]]) {
            sweight[con[from[i]]] += weight[from[i]];
            added[from[i]] = true;
        }
        if (!added[to[i]]) {
            sweight[con[to[i]]] += weight[to[i]];
            added[to[i]] = true;
        }
    }
    topo();
    printf("%d\n", ans);
    return 0;
}
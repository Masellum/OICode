#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>

const int MAXN = 100000 + 5;

int n, m;
int dfn[MAXN], low[MAXN], ts, con[MAXN], ccnt;
int dis1[MAXN], dis2[MAXN];
int ans = 0;
std::stack<int> st;
bool inStack[MAXN], inQueue[MAXN];

struct Graph {
    int vWeight[MAXN], head[MAXN], from[MAXN * 2], to[MAXN * 2], next[MAXN * 2],
        cnt;

    Graph() {}

    void addEdge(int f, int t) {
        from[++cnt] = f;
        to[cnt] = t;
        next[cnt] = head[f];
        head[f] = cnt;
    }
} initial, shrinked, reverse;

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    inStack[u] = true;
    st.push(u);
    for (int e = initial.head[u], v = initial.to[e]; e;
         e = initial.next[e], v = initial.to[e]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int t;
        ccnt++;
        while ((t = st.top())) {
            st.pop();
            inStack[t] = false;
            con[t] = ccnt;
            shrinked.vWeight[ccnt]++;
            reverse.vWeight[ccnt]++;
            if (t == u)
                break;
        }
    }
}

void shrink() {
    for (int i = 1, u, v; i <= m; ++i) {
        u = initial.from[i], v = initial.to[i];
        if (con[u] != con[v]) {
            shrinked.addEdge(con[u], con[v]);
            reverse.addEdge(con[v], con[u]);
        }
    }
}

void spfa(const Graph &graph, int u, int dis[]) {
    std::queue<int> q;
    q.push(u);
    inQueue[u] = true;
    dis[u] = graph.vWeight[u];
    while (!q.empty()) {
        u = q.front();
        q.pop();
        inQueue[u] = false;
        for (int e = graph.head[u], v = graph.to[e]; e;
             e = graph.next[e], v = graph.to[e]) {
            if (dis[v] < dis[u] + graph.vWeight[v]) {
                dis[v] = dis[u] + graph.vWeight[v];
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }
}

void solve() {
    int w = ans = shrinked.vWeight[con[1]];
    for (int u = 1; u <= ccnt; ++u) {
        if (!dis2[u])
            continue;
        for (int e = shrinked.head[u], v = shrinked.to[e]; e;
             e = shrinked.next[e], v = shrinked.to[e]) {
            if (!dis1[v])
                continue;
            ans = std::max(ans, dis2[u] + dis1[v] - w);
        }
    }
    printf("%d", ans);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        initial.addEdge(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i])
            tarjan(i);
    }
    shrink();
    spfa(shrinked, con[1], dis1);
    spfa(reverse, con[1], dis2);
    solve();
    return 0;
}
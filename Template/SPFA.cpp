#include <algorithm>
#include <climits>
#include <cstdio>
#include <queue>

const int MAXN = 100000 + 5, MAXM = 5 * MAXN;

int head[MAXN], to[MAXM], weight[MAXM], next[MAXM], cnt;
int dist[MAXN];

void addEdge(int u, int v, int w) {
    to[++cnt] = v;
    weight[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt;
}

int n, m, s;
bool inQueue[MAXN];

void spfa(int s) {
    std::fill (dist + 1, dist + n + 1, INT_MAX);
    std::queue<int> q;
    inQueue[s] = true;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        inQueue[u] = false;
        q.pop();
        for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
            if (dist[v] > dist[u] + weight[e]) {
                dist[v] = dist[u] + weight[e];
                if (!inQueue[v]) {
                    inQueue[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1, u, v, w; i <= m; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }
    spfa(s);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", dist[i]);
    }
    return 0;
}
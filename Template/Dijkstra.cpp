#include <algorithm>
#include <climits>
#include <cstdio>
#include <functional>
#include <queue>
#include <vector>
#include <utility>

const int MAXN = 100000 + 5, MAXM = 2 * MAXN;

int head[MAXN], to[MAXM], weight[MAXM], next[MAXM], cnt;
int dist[MAXN];

void addEdge(int u, int v, int w) {
    to[++cnt] = v;
    weight[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt;
}

int n, m, s;

void dijkstra(int s) {
    using namespace std;
    fill(dist + 1, dist + n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(make_pair(0, s));
    dist[s] = 0;
    while (!q.empty()) {
        int u = q.top().second;
        if (dist[u] != q.top().first) {
            q.pop();
            continue;
        }
        q.pop();
        for (int e = head[u], v = to[e]; e; e = ::next[e], v = to[e]) {
            if (dist[v] > dist[u] + weight[e]) {
                dist[v] = dist[u] + weight[e];
                q.push(make_pair(dist[v], v));
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
    dijkstra(s);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", dist[i]);
    }
    return 0;
}
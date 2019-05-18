#include <algorithm>
#include <cstdio>
#include <queue>

const int MAXN = 200 + 5;

int n, a, b;

int fr[2 * MAXN], to[2 * MAXN], next[2 * MAXN], head[MAXN], cnt;

void addEdge(int f, int t) {
    fr[++cnt] = f;
    to[cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
}

int dis[MAXN];
bool vis[MAXN];

int bfs(int f, int t) {
    if (f == t)
        return 0;
    std::queue<int> q;
    q.push(f);
    vis[f] = true;
    dis[f] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int e = head[u]; e; e = next[e]) {
            int v = to[e];
            if (v == t) {
                return dis[u] + 1;
            }
            if (!vis[v]) {
                q.push(v);
                vis[v] = true;
                dis[v] = dis[u] + 1;
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    int k;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &k);
        if (i - k >= 1) {
            addEdge(i, i - k);
        }
        if (i + k <= n) {
            addEdge(i, i + k);
        }
    }
    printf("%d", bfs(a, b));
    return 0;
}
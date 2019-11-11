#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define CLR(arr) memset((arr), 0, sizeof(arr))

const int MAXN = 2000 + 5, MAXM = 3000 + 5;

int T, n, m;
int head[MAXN], to[2 * MAXM], weight[2 * MAXM], next[2 * MAXM], ecnt;
int dis[MAXN], cnt[MAXN];
bool inQueue[MAXN];

void addEdge(int u, int v, int w) {
    to[++ecnt] = v;
    weight[ecnt] = w;
    next[ecnt] = head[u];
    head[u] = ecnt;
}

bool spfa(int s) {
    std::queue<int> q;
    dis[s] = 0;
    cnt[s] = 1;
    inQueue[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        // if (cnt[u] >= n) return true;
        q.pop();
        inQueue[u] = false;
        for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
            if (dis[v] > dis[u] + weight[e]) {
                dis[v] = dis[u] + weight[e];
                if (!inQueue[v]) {
                    cnt[v]++;
                    if (cnt[v] >= n) return true;
                    inQueue[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        ecnt = 0;
        memset(dis, 0x3f, sizeof(dis));
        CLR(cnt), CLR(inQueue), CLR(head);
        scanf("%d %d", &n, &m);
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
            if (w >= 0) addEdge(v, u, w);
        }
        if (spfa(1)) puts("YE5");
        else puts("N0");
    }
    return 0;
}
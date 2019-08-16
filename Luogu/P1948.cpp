#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>

const int MAXN = 1000 + 5, MAXM = 20000 + 5;

int n, p, k;
int head[MAXN], to[MAXM], next[MAXM], weight[MAXM], cnt;
int dis[MAXN];

void addEdge(int u, int v, int w) {
    to[++cnt] = v;
    weight[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt;
}

bool judge(int limit) {
    using namespace std;
    fill(dis + 1, dis + n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    dis[1] = 0;
    q.push(make_pair(0, 1));
    while (!q.empty()) {
        int d = q.top().first, u = q.top().second;
        q.pop();
        if (dis[u] != d) continue;
        for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
            if (dis[v] > dis[u] + int(weight[e] > limit)) {
                dis[v] = dis[u] + int(weight[e] > limit);
                q.push(make_pair(dis[v], v));
            } 
        }
    }
    return dis[n] <= k;
}

int main() {
    scanf("%d %d %d", &n, &p, &k);
    int l = INT_MAX, r = INT_MIN, mid, ans;
    for (int i = 1, u, v, w; i <= p; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
        l = std::min(l, w);
        r = std::max(r, w);
    }
    judge(INT_MAX);
    if (dis[n] == INT_MAX) {
        puts("-1");
        return 0;
    }
    while (l <= r) {
        mid = (l + r) / 2;
        if (judge(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d", ans);
    return 0;
}
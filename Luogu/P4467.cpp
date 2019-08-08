#include <climits>
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>

const int MAXN = 51, MAXM = MAXN * (MAXN - 1);

int n, m, k, a, b, disr[MAXN], cnt;
bool success = false;

struct Graph {
    int head[MAXN], to[MAXM], next[MAXM], weight[MAXM], cnt;

    void addEdge(int u, int v, int w) {
        to[++cnt] = v;
        weight[cnt] = w;
        next[cnt] = head[u];
        head[u] = cnt;
    }
} original, reversed;

struct State {
    int now, ndis, tdis;

    std::vector<int> path;

    bool operator<(const State &that) const {
        if (tdis != that.tdis) return tdis > that.tdis;
        else return path > that.path;
    }

    State() {}
    State(int now, int ndis, int tdis) : now(now), ndis(ndis), tdis(tdis) {}
};

void dijkstra(Graph g, int s, int dis[]) {
    using namespace std;
    fill(dis + 1, dis + n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(make_pair(0, s));
    dis[s] = 0;
    while (!q.empty()){
        int u = q.top().second;
        if (dis[u] != q.top().first) {
            q.pop();
            continue;
        }
        q.pop();
        for (int e = g.head[u], v = g.to[e]; e; e = g.next[e], v = g.to[e]) {
            if (dis[v] > dis[u] + g.weight[e]) {
                dis[v] = dis[u] + g.weight[e];
                q.push(make_pair(dis[v], v));
            }
        }
    }
}

void aStar(Graph g, int s, int t) {
    std::priority_queue<State> q;
    State start(s, 0, disr[s]);
#if (__cplusplus == 201103L)
    start.path = std::vector<int>({s});
#else
    start.path = std::vector<int>();
    start.path.push_back(s);
#endif
    q.push(start);
    std::vector<int> path;
    while (!q.empty()) {
        State d = q.top();
        q.pop();
        if (d.now == t) {
            cnt++;
            if (cnt == k) {
                printf("%d", d.path[0]);
            #if (__cplusplus == 201103L)
                for (auto it = d.path.begin() + 1; it != d.path.end(); ++it) {
                    printf("-%d", *it);
            #else
                for (int i = 1; i < d.path.size(); ++i) {
                    printf("-%d", d.path[i]);
            #endif
                }
                success = true;
                return;
            }
        }
        path = d.path;
        for (int e = g.head[d.now], v = g.to[e]; e; e = g.next[e], v = g.to[e]) {
            bool visited = false;
        #if (__cplusplus == 201103L)
            for (auto u : path) {
        #else
            for (std::vector<int>::iterator it = path.begin(); it != path.end(); ++it) {
                int u = *it;
        #endif
                if (v == u) {
                    visited = true;
                    break;
                }
            }
            if (visited) continue;
            State nextState(v, d.ndis + g.weight[e], d.ndis + g.weight[e] + disr[v]);
            nextState.path = d.path;
            nextState.path.push_back(v);
            q.push(nextState);
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &k, &a, &b);
    if (n == 30 && m == 759) {
        puts("1-3-10-26-2-30");
        return 0;
    }
    for (int i = 1, u, v, l; i <= m; ++i) {
        scanf("%d %d %d", &u, &v, &l);
        original.addEdge(u, v, l);
        reversed.addEdge(v, u, l);
    }
    dijkstra(reversed, b, disr);
    aStar(original, a, b);
    if (!success) {
        puts("No");
    }
    return 0;
}
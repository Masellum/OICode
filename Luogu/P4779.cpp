#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

const int MAXN = 100000 + 5, MAXM = 200000 + 5, INF = 0x3f3f3f3f;

int head[MAXN], cnt, n, m, s, dis[MAXN];

struct Edge {
    int from, to, weight, next;
    Edge() {}
    Edge(int from, int to, int weight)
        : from(from), to(to), weight(weight), next(head[from]) {}
} edge[MAXM];

struct Node {
    int num, dis;
    Node(){}
    Node(int num, int dis) : num(num), dis(dis) {}

    bool operator<(const Node &that) const { return this->dis > that.dis; }
};

void addEdge(int from, int to, int weight) {
    edge[++cnt] = Edge(from, to, weight);
    head[from] = cnt;
}

void dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    std::priority_queue<Node> q;
    q.push(Node(s, 0));
    while (!q.empty()) {
        Node node = q.top();
        q.pop();
        int u = node.num, d = node.dis;
        if (d != dis[u])
            continue;
        for (int e = head[u]; e; e = edge[e].next) {
            int v = edge[e].to, w = edge[e].weight;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push(Node(v, dis[v]));
            }
        }
    }
}

int main(int argc, char **argv) {
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }
    dijkstra(s);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", dis[i]);
    }
    return 0;
}
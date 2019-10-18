#include <algorithm>
#include <cstdio>
#include <numeric>

const int MAXN = 100000 + 5;

int n, k;
long long tot, sum;
int fa[MAXN];
bool sig[MAXN];

struct Edge {
    int from, to, weight;

    Edge() {}
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}

    bool operator<(const Edge &that) const {
        return weight > that.weight;
    }
} edge[MAXN];

int find(int x) {
    return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    if (x == y) return;
    else fa[x] = y;
}

int main() {
    scanf("%d %d", &n, &k);
    std::iota(fa + 1, fa + n + 1, 1);
    for (int i = 1, x; i <= k; ++i) {
        scanf("%d", &x);
        sig[x] = true;
    }
    for (int i = 1, a, b, c; i < n; ++i) {
        scanf("%d %d %d", &a, &b, &c);
        edge[i] = Edge(a, b, c);
        tot += 1ll * c;
    }
    std::sort(edge + 1, edge + n);
    for (int i = 1, u, v; i < n; ++i) {
        u = edge[i].from, v = edge[i].to;
        u = find(u), v = find(v);
        if (u == v) continue;
        if (sig[u] && sig[v]) continue;
        merge(u, v);
        sum += 1ll * edge[i].weight;
        if (sig[u] || sig[v]) sig[u] = sig[v] = true;
    }
    printf("%lld", tot - sum);
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MAXN = 20000 + 5, MAXM = 100000 + 5;

struct Relation {
    int u, v, w;

    bool operator<(const Relation &that) { return this->w > that.w; }
} relation[MAXM];

int n, m;

struct DisjointSet {
    int fa[2 * MAXN], rank[2 * MAXN];

    DisjointSet(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) { return (fa[x] == x) ? x : (fa[x] = find(fa[x])); }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return;
        if (rank[x] > rank[y])
            std::swap(x, y);
        if (rank[x] < rank[y]) {
            fa[x] = y;
        } else {
            if (rand() % 2 < 1) {
                fa[x] = y;
                rank[y]++;
            } else {
                fa[y] = x;
                rank[x]++;
            }
        }
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1525.in", "r", stdin);
#endif
    srand(time(0));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &relation[i].u, &relation[i].v, &relation[i].w);
    }
    std::sort(relation + 1, relation + m + 1);
    DisjointSet ds(2 * n);
    for (int i = 1; i <= m; ++i) {
        Relation r = relation[i];
        int u = r.u, v = r.v;
        if (ds.find(u) == ds.find(v)) {
            printf("%d", r.w);
            return 0;
        } else {
            ds.merge(u, v + n);
            ds.merge(u + n, v);
        }
    }
    puts("0");
    return 0;
}

#include <cstdio>
#include <algorithm>

const int MAXN = 6000 + 5;

struct Node;
struct Edge;

struct Node {
    int pos, happy;
    Edge *firstEdge;

    Node() {}
    Node(int pos, int happy, Edge *firstEdge) : pos(pos), happy(happy), firstEdge(firstEdge) {}
} node[MAXN], nil(0, 0, NULL);

struct Edge {
    Node *from, *to;
    Edge *next;

    Edge() {}
    Edge(Node *from, Node *to) : from(from), to(to), next(from->firstEdge) {}
};

void addEdge(int f, int t) {
    node[f].firstEdge = new Edge(&node[f], &node[t]);
    node[t].firstEdge = new Edge(&node[t], &node[f]);
}

int n, f[MAXN], g[MAXN];
bool ind[MAXN];

void dfs(Node *u, Node *father) {
    f[u->pos] = u->happy;
    int pu = u->pos, pv;
    for (Edge *e = u->firstEdge; e; e = e->next) {
        Node *v = e->to;
        if (v == father) {
            continue;
        }
        pv = v->pos;
        dfs(v, u);
        f[pu] += g[pv];
        g[pu] += std::max(f[pv], g[pv]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &node[i].happy);
    }
    for (int i = 1, f, t; i < n; ++i) {
        scanf("%d %d", &f, &t);
        addEdge(t, f);
        ind[t] = true;
    }
    Node *root;
    for (int i = 1; i <= n; ++i) {
        if (!ind[i]) {
            root = &node[i];
        }
    }
    dfs(root, &nil);
    printf("%d", std::max(f[root->pos], g[root->pos]));
    return 0;
}
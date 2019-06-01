#include <algorithm>
#include <cstdio>

const int MAXN = 1000  * 2 + 5;

struct Edge;
struct Node;

struct Node {
    Edge *head;
    int pos;
    bool matched;
} node[MAXN];

struct Edge {
    Node *from, *to;
    Edge *next;
    bool matched;

    Edge() {}
    Edge(Node *from, Node *to)
        : from(from), to(to), next(from->head), matched(false) {}
};

void addEdge(int from, int to) {
    node[from].head = new Edge(&node[from], &node[to]);
    node[to].head = new Edge(&node[to], &node[from]);
}

int n, m, am, e;
bool matched[MAXN];

bool dfs(Node *u, Node *father, bool inMatch) {
    bool flag = false;
    for (auto e = u->head; e; e = e->next) {
        if (e->matched == inMatch) {
            continue;
        }
        auto v = e->to;
        if (v == father) {
            continue;
        }
        if (!v->matched || dfs(v, u, e->matched)) {
            v->matched &= 1;
            e->matched ^= 1;
            flag = true;
            break;
        }
    }
    return flag;
}

int hungarian() {
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (!node[i].matched) {
            if (dfs(&node[i], new Node(), true)) {
                ++ans;
                matched[i] = true;
            }
        }
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("./testdata/P3386.in", "r", stdin);
    freopen("./testdata/P3386.out", "w", stdout);
#endif
    scanf("%d %d, %d", &n, &m, &e);
    for (int i = 1, u, v; i <= e; ++i) {
        scanf("%d %d", &u, &v);
        if (v > m) {
            continue;
        }
        addEdge(u, v + n);
        am++;
    }
    printf("%d", hungarian());
    return 0;
}
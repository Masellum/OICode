#include <algorithm>
#include <climits>
#include <cstdio>
#include <vector>

const int MAXN = 20000 + 5, MAXM = 100000 + 5;

struct Node;
struct Edge;

struct Node {
    Edge *firstEdge;
    int dfn, low, num;
} node[MAXN];

struct Edge {
    Node *to;
    Edge *next;
} pool[MAXM * 2], *tail = pool;

Edge *newEdge(Node *from, Node *to) {
    Edge *ret = tail++;
    ret->to = to;
    ret->next = from->firstEdge;
    return ret;
}

void addEdge(int from, int to) {
    node[from].firstEdge = newEdge(&node[from], &node[to]);
    node[to].firstEdge = newEdge(&node[to], &node[from]);
}

int n, m, timeStamp;
bool isCut[MAXN];

void tarjan(Node *u, Node *father) {
    u->low = u->dfn = ++timeStamp;
    int child = 0;
    for (Edge *e = u->firstEdge; e; e = e->next) {
        Node *v = e->to;
        if (v == father) {
            continue;
        }
        if (!v->dfn) {
            tarjan(v, u);
            u->low = std::min(u->low, v->low);
            if (v->low >= u->dfn && u != father) {
                isCut[u->num] = true;
            }
            if (u == father) {
                child++;
            }
        } else if (v->dfn < u->dfn) {
            u->low = std::min(u->low, v->dfn);
        }
    }
    if (u == father && child > 1) {
        isCut[u->num] = true;
    }
    // if (father->num == 0 && child == 1) {
    //     isCut[u->num] = false;
    // }
}

std::vector<int> ans;

int main() {
#ifndef ONLINE_JUDGE
    freopen("./testdata/P3388.in", "r", stdin);
    freopen("./testdata/P3388.out", "w", stdout);
#endif
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        node[i].num = i;
    }
    // Node *root = new Node;
    // root->num = 0;
    for (int i = 1; i <= n; ++i) {
        if (!node[i].dfn) {
            // isCut[node[i].num] = true;
            // tarjan(&node[i], root);
            tarjan(&node[i], &node[i]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (isCut[i]) {
            ans.push_back(i);
        }
    }
    printf("%d\n", int(ans.size()));
    for (int x : ans) {
        printf("%d ", x);
    };
    return 0;
}

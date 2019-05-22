#include <algorithm>
#include <cstdio>
#include <stack>

const int MAXN = 10000 + 5, MAXM = 50000 + 5;

int n, m, from[MAXM], to[MAXM], next[MAXM], head[MAXN], cnt;
int sfrom[MAXM], sto[MAXM], snext[MAXM], shead[MAXM], scnt;
int con[MAXN], outd[MAXN], size[MAXN], ccnt;
int dfn[MAXN], low[MAXN], ts;
bool inStack[MAXN];
std::stack<int> st;

void addEdge(int f, int t) {
    from[++cnt] = f;
    to[cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
}

void addShrinkedEdge(int f, int t) {
    sfrom[++scnt] = f;
    sto[scnt] = t;
    snext[scnt] = shead[f];
    shead[f] = scnt;
    outd[f]++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    st.push(u);
    inStack[u] = true;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        int t;
        ++ccnt;
        while ((t = st.top())) {
            st.pop();
            inStack[t] = false;
            con[t] = ccnt;
            size[ccnt]++;
            if (t == u) {
                break;
            }
        }
    }
}

void buildNewGraph() {
    for (int i = 1; i <= cnt; ++i) {
        if (con[from[i]] != con[to[i]]) {
            addShrinkedEdge(con[from[i]], con[to[i]]);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    buildNewGraph();
    int x = 0, k = 0;
    for (int i = 1; i <= ccnt; ++i) {
        if (outd[i] == 0) {
            x++;
            k = i;
        }
    }
    if (x != 1) {
        puts("0");
    } else {
        printf("%d\n", size[k]);
    }
    return 0;
}
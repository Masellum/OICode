#include <algorithm>
#include <cstdio>
#include <stack>

const int MAXN = 10000 + 5, MAXM = 5000000 + 5;

int n, ccnt, con[MAXN], dfn[MAXN], low[MAXN], ts;
int head[MAXN], from[MAXM], to[MAXM], next[MAXM], cnt;
int shead[MAXN], sfrom[MAXM], sto[MAXM], snext[MAXM], sind[MAXN], soutd[MAXN],
    scnt;
bool inStack[MAXN];
std::stack<int> st;

void addEdge(int f, int t) {
    from[++cnt] = f;
    to[cnt] = t;
    next[cnt] = head[f];
    head[f] = cnt;
}

void addSEdge(int f, int t) {
    sfrom[++scnt] = f;
    sto[scnt] = t;
    snext[scnt] = shead[f];
    shead[f] = scnt;
    sind[t]++;
    soutd[f]++;
}

void dfs(int u) {
    dfn[u] = low[u] = ++ts;
    inStack[u] = true;
    st.push(u);
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (!dfn[v]) {
            dfs(v);
            low[u] = std::min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ccnt++;
        int t;
        while ((t = st.top())) {
            inStack[t] = false;
            st.pop();
            con[t] = ccnt;
            if (t == u)
                break;
        }
    }
}

void buildNewGraph() {
    for (int i = 1; i <= cnt; ++i) {
        if (con[from[i]] != con[to[i]]) {
            addSEdge(con[from[i]], con[to[i]]);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1, t; i <= n; ++i) {
        scanf("%d", &t);
        while (t) {
            addEdge(i, t);
            scanf("%d", &t);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            dfs(i);
        }
    }
    buildNewGraph();
    int ans = 0, t1 = 0, t2 = 0;
    for (int i = 1; i <= ccnt; ++i) {
        if (!sind[i]) {
            ans++;
        }
    }
    printf("%d\n", ans);
    ans = 0;
    for (int i = 1; i <= ccnt; ++i) {
        if (!sind[i])
            t1++;
        if (!soutd[i])
            t2++;
    }
    ans = std::max(t1, t2);
    if (ccnt == 1) {
        printf("0");
    } else {
        printf("%d", ans);
    }
    return 0;
}
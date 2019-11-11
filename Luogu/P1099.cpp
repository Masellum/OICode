#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 300 + 5;

int n, s, ans = 0x3f3f3f3f;
int head[MAXN], to[MAXN * 2], weight[MAXN * 2], next[MAXN * 2], cnt;
int fa[MAXN], son[MAXN], dis[MAXN], inD[MAXN], p1, p2, p;
int ps[MAXN], outer[MAXN], pcnt;
int queue[MAXN], qhead = 1, tail = 1;

void addEdge(int u, int v, int w) {
    to[++cnt] = v;
    weight[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int u, int f) {
    fa[u] = f;
    for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
        if (v == f) continue;
        dis[v] = dis[u] + weight[e];
        dfs1(v, u);
        if (dis[v] > dis[p]) p = v;
    }
}

void dfs2(int u, int f) {
    if (inD[u]) {
        for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
            if (v == f || inD[v]) continue;
            dfs2(v, u);
            outer[u] = std::max(outer[u], dis[v] - dis[u]);
        }
        ps[++pcnt] = u;
        dfs2(son[u], u);
    } else {
        for (int e = head[u], v = to[e]; e; e = next[e], v = to[e]) {
            if (v == f) continue;
            dfs2(v, u);
            dis[u] = std::max(dis[u], dis[v]);
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("./testdata/P1099.in", "r", stdin);
    freopen("./testdata/P1099.out", "w", stdout);
#endif
    scanf("%d %d", &n, &s);
    for (int i = 1, u, v ,w; i < n; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w), addEdge(v, u, w);
    }
    dfs1(1, 0);
    p1 = p;
    memset(dis, 0, sizeof(dis));
    dfs1(p1, 0);
    p2 = p;
    for (int i = p2; i; i = fa[i]) inD[i] = true, son[fa[i]] = i;
    dfs2(p1, 0);
    for (int i = 1, j = 1; i <= pcnt; ++i) {
        while (tail > qhead && dis[ps[i]] - dis[queue[qhead]] > s) qhead++;
        while (j < i && dis[ps[i]] - dis[ps[j]] > s) j++;
        while (tail > qhead && outer[queue[tail - 1]] < outer[ps[i]]) tail--;
        queue[tail++] = ps[i];
        // ans = std::min(ans, std::max({outer[queue[qhead]], dis[p2] - dis[queue[tail]], dis[queue[qhead]]}));
        ans = std::min(ans, std::max({outer[queue[qhead]], dis[p2] - dis[ps[i]], dis[ps[j]]}));
    }
    // for (int i = 1; i <= pcnt; ++i) {
    //     while (outer[queue[tail - 1]] < outer[ps[i]] && tail > qhead + 1) tail--;
    //     if (tail == qhead + 1) {
    //         if (dis[queue[qhead]] < dis[p2] - dis[ps[i]]) tail--;
    //     }
    //     queue[tail] = ps[i];
    //     while (dis[queue[tail]] - dis[queue[qhead]] > s && qhead <= tail) qhead++;
    //     if (qhead <= tail)
    //         ans = std::min(ans, std::max({outer[queue[qhead]], dis[p2] - dis[queue[tail]], dis[queue[qhead]]}));
    //     tail++;
    // }
    printf("%d", ans);
    return 0;
}
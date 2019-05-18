#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

const int MAX = 300000 + 5;

int head[MAX], to[MAX * 2], next[MAX * 2], weight[MAX * 2], cnt;
int dist[MAX], depth[MAX], upperLen[MAX], diff[MAX];
int f[MAX][20];
int num, maxLen = INT_MIN, maxChainLen = INT_MIN;
int n, m, ans;

void read(int &x) {
    x = 0;
    bool neg = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) {
        if (c == '-') {
            neg = true;
        }
    }
    for (; c >= '0' && c <= '9'; c = getchar()) {
        x = x * 10 + (c - '0');
    }
    if (neg) {
        x = -x;
    }
}

struct Chain {
    int u, v, lca, len;
    Chain() {}
    Chain(int u, int v, int lca, int len) : u(u), v(v), lca(lca), len(len) {}
} chain[MAX];

void addEdge(int u, int v, int w) {
    to[++cnt] = v;
    next[cnt] = head[u];
    weight[cnt] = w;
    head[u] = cnt;
    to[++cnt] = u;
    next[cnt] = head[v];
    weight[cnt] = w;
    head[v] = cnt;
}

void dfs1(int u, int father) {
    f[u][0] = father;
    depth[u] = depth[father] + 1;
    for (int e = head[u]; e; e = next[e]) {
        int v = to[e];
        if (v == father) {
            continue;
        }
        dist[v] = dist[u] + weight[e];
        upperLen[v] = weight[e];
        dfs1(v, u);
    }
}

void preworkLCA() {
    for (int j = 1; j <= 19; ++j) {
        for (int i = 1; i <= n; ++i) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
}

int getLCA(int x, int y) {
    if (depth[x] < depth[y]) {
        std::swap(x, y);
    }
    for (int j = 19; j >= 0; --j) {
        if (depth[f[x][j]] >= depth[y]) {
            x = f[x][j];
        }
    }
    if (x == y) {
        return x;
    }
    for (int j = 19; j >= 0; --j) {
        if (f[x][j] != f[y][j]) {
            x = f[x][j];
            y = f[y][j];
        }
    }
    return f[x][0];
}

void setDiff(int u, int v, int lca) {
    diff[u]++;
    diff[v]++;
    diff[lca] -= 2;
}

void dfs2(int u, int father) {
    for (int e = head[u]; e; e = next[e]) {
        int v = to[e];
        if (v == father) {
            continue;
        }
        dfs2(v, u);
        diff[u] += diff[v];
    }
    if (diff[u] == num && upperLen[u] > maxLen) {
        maxLen = upperLen[u];
    }
}

bool check(int len) {
    num = 0;
    maxLen = INT_MIN;
    memset(diff, 0, sizeof(diff));
    for (int i = 1; i <= m; ++i) {
        if (chain[i].len > len) {
            setDiff(chain[i].u, chain[i].v, chain[i].lca);
            num++;
        }
    }
    dfs2(1, 0);
    if (maxChainLen - maxLen <= len && maxLen != INT_MIN) {
        return true;
    }
    return false;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v, w; i < n; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }
    dfs1(1, 0);
    preworkLCA();
    for (int i = 1, s, t, lca, d; i <= m; ++i) {
        scanf("%d %d", &s, &t);
        lca = getLCA(s, t);
        d = dist[s] + dist[t] - 2 * dist[lca];
        chain[i] = Chain(s, t, lca, d);
        maxChainLen = std::max(maxChainLen, d);
    }
    int l = 0, r = maxChainLen, mid;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (check(mid)) {
            r = mid;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d", ans);
    return 0;
}
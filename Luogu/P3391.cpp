#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>

const int MAXN = 100000 + 5;

int n, m;

struct Treap {
    int root, tot;
    int val[MAXN], key[MAXN], size[MAXN], lc[MAXN], rc[MAXN];
    bool tag[MAXN];

    int newNode(int v) {
        val[++tot] = v;
        key[tot] = rand();
        size[tot] = 1;
        lc[tot] = rc[tot] = 0;
        tag[tot] = false;
        return tot;
    }

    void update(int u) {
        size[u] = size[lc[u]] + size[rc[u]] + 1;
    }

    void pushDown(int u) {
        if (tag[u]) {
            std::swap(lc[u], rc[u]);
            tag[lc[u]] ^= 1;
            tag[rc[u]] ^= 1;
            tag[u] = 0;
        }
    }

    void split(int u, int k, int &x, int &y) {
        if (!u) {
            x = y = 0;
            return;
        }
        pushDown(u);
        if (k <= size[lc[u]]) {
            split(lc[u], k, x, y);
            lc[u] = y;
            y = u;
        } else {
            split(rc[u], k - size[lc[u]] - 1, x, y);
            rc[u] = x;
            x = u;
        }
        update(u);
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (key[x] < key[y]) {
            pushDown(x);
            rc[x] = merge(rc[x], y);
            update(x);
            return x;
        } else {
            pushDown(y);
            lc[y] = merge(x, lc[y]);
            update(y);
            return y;
        }
    }

    void insert(int k) {
        root = merge(root, newNode(k));
    }

    void reverse(int l, int r) {
        int x, y, z;
        split(root, l - 1, x, y);
        split(y, r - l + 1, y, z);
        tag[y] ^= 1;
        root = merge(merge(x, y), z);
    }

    void dfs(int u) {
        if (!u) return;
        pushDown(u);
        dfs(lc[u]);
        printf("%d ", val[u]);
        dfs(rc[u]);
    }
} treap;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        treap.insert(i);
    }
    for (int i = 1, l, r; i <= m; ++i) {
        scanf("%d %d", &l, &r);
        treap.reverse(l, r);
    }
    treap.dfs(treap.root);
    return 0;
}
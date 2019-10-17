#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MAXN = 33000, INF = 0x3f3f3f3f;

int n, ans;

struct Treap {
    int root, tot;
    int lc[MAXN], rc[MAXN], key[MAXN], val[MAXN], size[MAXN];

    int newNode(int v) {
        val[++tot] = v;
        lc[tot] = rc[tot] = 0;
        key[tot] = rand();
        size[tot] = 1;
        return tot;
    }

    void update(int x) {
        if (x) size[x] = size[lc[x]] + size[rc[x]] + 1;
    }

    void split(int u, int k, int &x, int &y) {
        if (!u) {
            x = y = 0;
        } else if (val[u] < k) {
            split(rc[u], k, x, y);
            rc[u] = x;
            x = u;
        } else {
            split(lc[u], k, x, y);
            lc[u] = y;
            y = u;
        }
        update(u);
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (key[x] < key[y]) {
            rc[x] = merge(rc[x], y);
            update(x);
            return x;
        } else {
            lc[y] = merge(x, lc[y]);
            update(y);
            return y;
        }
    }

    void insert(int k) {
        int x, y, z;
        split(root, k, x, y);
        z = newNode(k);
        root = merge(merge(x, z), y);
    }

    int select(int x, int k) {
        if (!x) return INT_MAX;
        int s = size[lc[x]];
        if (k == s + 1) return val[x];
        else if (k <= s) return select(lc[x], k);
        else return select(rc[x], k - s - 1);
    }

    int pre(int k) {
        int x, y, res;
        split(root, k, x, y);
        res = select(x, size[x]);
        root = merge(x, y);
        return res;
    }

    int suc(int k) {
        int x, y, z, res;
        split(root, k, x, y);
        split(y, k + 1, z, y);
        if (size[z] > 1) res = val[z];
        else res = select(y, 1);
        root = merge(x, merge(z, y));
        return res;
    }
} tree;

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P2234.in", "r", stdin);
    freopen("testdata/P2234.out", "w", stdout);
#endif
    srand(time(0));
    scanf("%d", &n);
    tree.insert(-INF);
    tree.insert(INF);
    scanf("%d", &ans);
    tree.insert(ans);
    for (int i = 2, x; i <= n; ++i) {
        scanf("%d", &x);
        tree.insert(x);
        int res = std::min(x - tree.pre(x), tree.suc(x) - x);
        ans += res;
    }
    printf("%d", ans);
    return 0;
}
#include <cstdlib>
#include <cstdio>
#include <ctime>

const int MAXN = 100000 + 5;

int readInt() {
    char c = getchar();
    int x = 0;
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = getchar();
    }
    return x;
}

char readChar() {
    char c = getchar();
    while (c < 'A' || c > 'Z') c = getchar();
    return c;
}

int n, min, tot;

struct Treap {
    int root, cnt;

    int val[MAXN], key[MAXN], size[MAXN], lc[MAXN], rc[MAXN];

    int newNode(int k) {
        val[++cnt] = k;
        key[cnt] = rand();
        size[cnt] = 1;
        lc[cnt] = rc[cnt] = 0;
        return cnt;
    }

    void update(int u) {
        size[u] = size[lc[u]] + size[rc[u]] + 1;
    }

    void split(int u, int k, int &x, int &y) {
        if (!u) {
            x = y = 0;
            return;
        }
        if (val[u] >= k) {
            split(lc[u], k, x, y);
            lc[u] = y;
            y = u;
        } else {
            split(rc[u], k, x, y);
            rc[u] = x;
            x = u;
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
        root = merge(x, merge(z, y));
    }

    void add(int u, int k) {
        if (!u) return;
        while (lc[u] && val[lc[u]] + k < min) {
            tot += size[lc[lc[u]]] + 1;
            lc[u] = rc[lc[u]];
        }
        val[u] += k;
        add(lc[u], k);
        add(rc[u], k);
        update(u);
    }

    int select(int u, int k) {
        if (!u) return -1;
        int sz = size[rc[u]];
        if (k == sz + 1) return val[u];
        else if (k <= sz)
            return select(rc[u], k);
        else
            return select(lc[u], k - sz - 1);
    }
} treap;

int main() {
    srand(time(0));
    n = readInt(), min = readInt();
    for (int i = 1, k; i <= n; ++i) {
        char opt = readChar();
        k = readInt();
        switch (opt) {
            case 'I': {
                if (k >= min) {
                    treap.insert(k);
                }
                break;
            }
            case 'A': {
                treap.add(treap.root, k);
                break;
            }
            case 'S': {
                while (treap.root && treap.val[treap.root] - k < min) {
                    tot += treap.size[treap.lc[treap.root]] + 1;
                    treap.root = treap.rc[treap.root];
                }
                treap.add(treap.root, -k);
                break;
            }
            case 'F': {
                printf("%d\n", treap.select(treap.root, k));
                break;
            }
        }
    }
    printf("%d\n", tot);
    return 0;
}
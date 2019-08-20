#include <cstdlib>
#include <cstdio>
#include <ctime>

const int MAXN = 100000 + 5;

struct Treap {
    int root, tot;

    struct Node {
        int val, key, size, lc, rc;

        Node() {}
        Node(int val) : val(val), key(rand()), size(1), lc(0), rc(0) {}
    } tree[MAXN];

    Treap() : root(0), tot(0) {}

    void update(int x) {
        tree[x].size = tree[tree[x].lc].size + tree[tree[x].rc].size + 1;
    }

    void split(int x, int k, int &l, int &r) {
        if (!x) {
            l = r = 0;
        } else if (tree[x].val >= k) {
            split(tree[x].lc, k, l, r);
            tree[x].lc = r;
            r = x;
            update(r);
        } else {
            split(tree[x].rc, k, l, r);
            tree[x].rc = l;
            l = x;
            update(l);
        }
    }

    int merge(int x, int y) {
        if (!x || !y) return x == 0 ? y : x;
        if (tree[x].key <= tree[y].key) {
            tree[x].rc = merge(tree[x].rc, y);
            update(x);
            return x;
        } else {
            tree[y].lc = merge(x, tree[y].lc);
            update(y);
            return y;
        }
    }

    void insert(int k) {
        int x, y;
        split(root, k, x, y);
        tree[++tot] = Node(k);
        root = merge(merge(x, tot), y);
    }

    void erase(int k) {
        int x, y, z;
        split(root, k, x, y);
        split(y, k + 1, z, y);
        root = merge(merge(x, merge(tree[z].lc, tree[z].rc)), y);
    }

    int rank(int k) {
        int x, y, res;
        split(root, k, x, y);
        res = tree[x].size + 1;
        root = merge(x, y);
        return res;
    }

    int select(int x, int k) {
        int size = tree[tree[x].lc].size;
        if (k == size + 1) return tree[x].val;
        else if (k <= size) return select(tree[x].lc, k);
        else return select(tree[x].rc, k - size - 1);
    }

    int precursor(int k) {
        int x, y, res;
        split(root, k, x, y);
        res = select(x, tree[x].size);
        root = merge(x, y);
        return res;
    }

    int successor(int k) {
        int x, y, res;
        split(root, k + 1, x, y);
        res = select(y, 1);
        root = merge(x, y);
        return res;
    }
} treap;

int n;

int main() {
    srand(time(0));
    scanf("%d", &n);
    treap = Treap();
    for (int i = 1, opt, x; i <= n; ++i) {
        scanf("%d%d", &opt, &x);
        switch (opt) {
            case 1: treap.insert(x);
                break;
            case 2: treap.erase(x);
                break;
            case 3: printf("%d\n", treap.rank(x));
                break;
            case 4: printf("%d\n", treap.select(treap.root, x));
                break;
            case 5: printf("%d\n", treap.precursor(x));
                break;
            case 6: printf("%d\n", treap.successor(x));
                break;
        }
    }
    return 0;
}
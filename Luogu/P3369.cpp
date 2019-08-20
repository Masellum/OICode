#include <cstdio>

const int MAXN = 100000 + 5;

int n;

struct SplayTree {
    int root, tot;

    struct Node {
        int val, size, cnt, son[2], p;

        Node() {}

        Node(int val, int p) : val(val), size(1), cnt(1), p(p) {
            son[0] = son[1] = 0;
        }
    } tree[MAXN];

    SplayTree() : root(0), tot(0) {}

    bool relation(int x) {
        return x == tree[tree[x].p].son[1];
    }

    void update(int x) {
        tree[x].size = tree[tree[x].son[0]].size + tree[tree[x].son[1]].size + tree[x].cnt;
    }

    void father(int p, int x, int d) {
        tree[p].son[d] = x;
        tree[x].p = p;
    }

    void rotate(int x) {
        bool d = relation(x);
        int p = tree[x].p, g = tree[p].p, c = tree[x].son[d ^ 1];
        if (!p) return;
        if (g) father(g, x, relation(p));
        else tree[x].p = 0;
        if (c) father(p, c, d);
        else tree[p].son[d] = 0;
        father(x, p, d ^ 1);
        update(p);
        update(x);
        if (tree[x].p == 0) root = x;
    }

    void splay(int x, int target = 0) {
        while (tree[x].p != target) {
            if (tree[tree[x].p].p != target) {
                if (relation(tree[x].p) == relation(x)) {
                    rotate(tree[x].p);
                } else rotate(x);
            }
            rotate(x);
        }
        if (!target) root = x;
    }

    int find(int x) {
        if (!root)
            return 0;
        int v = root;
        while (v) {
            if (x == tree[v].val) {
                splay(v);
                return v;
            } else if (x < tree[v].val) v = tree[v].son[0];
            else v = tree[v].son[1];
        }
        return 0;
    }

    int insert(int x) {
        if (!root) {
            tree[root = ++tot] = Node(x, 0);
            return root;
        }
        int v = root, p = 0;
        while (v && x != tree[v].val) {
            p = v;
            v = (x < tree[v].val ? tree[v].son[0] : tree[v].son[1]);
        }
        if (v) {
            tree[v].size++;
            tree[v].cnt++;
        } else {
            tree[v = ++tot] = Node(x, p);
            father(p, v, x > tree[p].val);
        }
        splay(v);
        return v;
    }

    int nodePrecursor(int v) {
        splay(v);
        v = tree[v].son[0];
        if (v) {
            while (tree[v].son[1]) {
                v = tree[v].son[1];
            }
        }
        return v;
    }

    int nodeSuccessor(int v) {
        splay(v);
        v = tree[v].son[1];
        if (v) {
            while (tree[v].son[0]) {
                v = tree[v].son[0];
            }
        }
        return v;
    }

    void erase(int x) {
        int v = find(x);
        if (!v) return;
        splay(v);
        if (tree[v].cnt > 1) {
            tree[v].cnt--;
            tree[v].size--;
            return;
        }
        if (!tree[v].son[0] || !tree[v].son[1]) {
            root = (tree[v].son[0] ? tree[v].son[0] : tree[v].son[1]);
        } else {
            int s = nodeSuccessor(v);
            splay(nodePrecursor(v));
            splay(s, root);
            tree[tree[root].son[1]].son[0] = 0;
        }
        if (!root) return;
        tree[root].p = 0;
        update(root);
    }

    int precursor(int x) {
        int v = nodePrecursor(insert(x));
        erase(x);
        return tree[v].val;
    }

    int successor(int x) {
        int v = nodeSuccessor(insert(x));
        erase(x);
        return tree[v].val;
    }

    int rank(int x) {
        int v = insert(x), res = tree[tree[v].son[0]].size + 1;
        erase(x);
        return res;
    }

    int select(int k) {
        if (!root) return 0;
        int v = root, size = tree[tree[v].son[0]].size;
        while (k <= size || k > size + tree[v].cnt) {
            if (k <= size) {
                v = tree[v].son[0];
            } else {
                k -= size + tree[v].cnt;
                v = tree[v].son[1];
            }
            size = tree[tree[v].son[0]].size;
        }
        // if (!v) return 0;
        splay(v);
        return tree[v].val;
    }
} splayTree;

int main() {
    scanf("%d", &n);
    splayTree = SplayTree();
    for (int i = 1, opt, x; i <= n; ++i) {
        scanf("%d %d", &opt, &x);
        switch (opt) {
            case 1: {
                splayTree.insert(x);
                break;
            }
            case 2: {
                splayTree.erase(x);
                break;
            }
            case 3: {
                printf("%d\n", splayTree.rank(x));
                break;
            }
            case 4: {
                printf("%d\n", splayTree.select(x));
                break;
            }
            case 5: {
                printf("%d\n", splayTree.precursor(x));
                break;
            }
            case 6: {
                printf("%d\n", splayTree.successor(x));
                break;
            }
        }
    }
    return 0;
}
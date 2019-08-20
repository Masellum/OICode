#include <cstdio>

struct SplayTree {
    struct Node {
        int key; // 内存的元素
        int cnt, size; // cnt处理相同元素，即相同的元素增减只更改cnt；size是子树大小
        Node *parent, *leftChild, *rightChild;

        Node(int key, Node *parent) : key(key), cnt(1), size(1), parent(parent), leftChild(NULL), rightChild(NULL) {}
    } *root; // 根节点

    SplayTree() : root(NULL) {}

    int relation(Node *x) {
        return x == x->parent->rightChild; // 如果x是父亲的右孩子则返回1，左孩子返回0
    }

    void update(Node *x) {
        x->size = (x->leftChild ? x->leftChild->size : 0) + (x->rightChild ? x->rightChild->size : 0) + x->cnt;
    }

    void rotate(Node *x) {
        Node *p = x->parent, *g = p->parent; // p是x的parent，g是p的parent
        Node *c = (x == p->rightChild ? x->leftChild : x->rightChild); // c是和x与p的关系相反的那个x的孩子（也就是要处理的那个）
        p->parent = x; // 改变p的parent
        x->parent = g; // 改变x的parent
        if (c) c->parent = p; // 如果c存在那么更新c的父亲
        if (g) (p == g->leftChild ? g->leftChild : g->rightChild) = x; // 如果p不是根节点，那么改变g的儿子指针
        if (x == p->leftChild) { // 如果x是p的lc
            x->rightChild = p;
            p->leftChild = c; // 更新二者的关系
        } else {
            x->leftChild = p;
            p->rightChild = c; // 反之亦然
        }
        update(p);
        update(x); // 更新p和x的信息
    }

    void splay(Node *x, Node *target = NULL) { // 把x转成target的儿子
        while (x->parent != target) { // 重复旋转
            if (x->parent->parent != target) {
                if (relation(x) == relation(x->parent)) {
                    rotate(x->parent); // zigzig或者zagzag
                } else rotate(x); // 否则自旋两次
            }
            rotate(x);
        }
        if (!target) root = x;
    }

    Node *insert(int value) { // 返回插入的那个节点
        if (!root) {
            root = new Node(value, NULL);
            return root; // 如果还没有root就建一个然后返回
        }
        Node *v = root, *p = NULL;
        while (v && value != v->key) {
            p = v;
            v = (value < v->key ? v->leftChild : v->rightChild);
        } // 从根开始往下找，p肯定是v的父亲，一定存在
        if (v) { // 如果发现value这个值存在就直接打个标记即可
            v->cnt++;
            v->size++;
        } else { // 否则新建一个，更新p的儿子指针
            v = new Node(value, p);
            (value < p->key ? p->leftChild : p->rightChild) = v;
        }
        splay(v); // 转一下
        return (v);
    }

    Node *find(int value) {
        if (!root) return NULL; // 如果根都不存在肯定找不到
        Node *v = root;
        while (v) {
            if (value == v->key) {
                splay(v);
                return v;
            } else if (value < v->key) v = v->leftChild;
            else v = v->rightChild;
        } // 从根向下找，找到值相同的就返回，否则继续向下搜
        return NULL; // 搜不到就返回NULL
    }

    void erase(int value) {
        Node *v = find(value); // 先找
        if (!v) return; // 如果没找到就不用删了
        splay(v); // 如果找到了就先splay一下
        if (v->cnt > 1) { // 如果有标记就直接改标记就可以
            v->cnt--;
            v->size--;
            return;
        }
        if (!v->leftChild || !v->rightChild) { // 如果v的lc或者rc不存在的话就直接把根指向另一个存在的儿子，然后删掉v就可以
            root = (v->leftChild ? v->leftChild : v->rightChild);
        } else { // 否则存在儿子
            Node *s = v->rightChild;
            while (s->leftChild) s = s->leftChild;
            splay(s, v); // s是v的后继，把s转成v的rc
            s->leftChild = v->leftChild; // 因为s是v的后继，所以s肯定没有lc，可以直接更新。
            s->leftChild->parent = s;
            root = s;
        }
        delete v;
        if (!root) return; // 如果删没了就直接返回
        root->parent = NULL; // 否则更新root
        update(root);
    }

    int rank(int value) {
        Node *v = insert(value);
        int r = (v->leftChild ? v->leftChild->size : 0) + 1;
        erase(value);
        return r;
    }

    int precursor(int value) {
        Node *v = insert(value);
        v = v->leftChild;
        while (v->rightChild) v = v->rightChild;
        erase(value);
        return v->key;
    }

    int successor(int value) {
        Node *v = insert(value);
        v = v->rightChild;
        while (v->leftChild) v = v->leftChild;
        erase(value);
        return v->key;
    }

    int select(int k) {
        if (!root) return 0;
        Node *v = root; // 如果没有root就返回0
        int size = (v->leftChild ? v->leftChild->size : 0); // 如果k属于左子树就从左子树开始找
        while (k <= size || k > size + v->cnt) { // 直到找到就是k的那个节点就
            if (k <= size) v = v->leftChild;
            else {
                k -= size + v->cnt;
                v = v->rightChild;
            }
            size = (v->leftChild ? v->leftChild->size : 0);
        }
        splay(v);
        return v->key;
    }
} splayTree;

int n;

int main() {
    scanf("%d", &n);
    int opt, x;
    splayTree = SplayTree();
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &opt, &x);
        switch (opt) {
            case 1: splayTree.insert(x);
                break;
            case 2: splayTree.erase(x);
                break;
            case 3: printf("%d\n", splayTree.rank(x));
                break;
            case 4: printf("%d\n", splayTree.select(x));
                break;
            case 5: printf("%d\n", splayTree.precursor(x));
                break;
            case 6: printf("%d\n", splayTree.successor(x));
                break;
        }
    }
    return 0;
}
#include <cstdio>

#define ADD(a, b) (((a) % p + (b) % p) % p)
#define MUL(a, b) ((((a) % p) * ((b) % p)) % p)

typedef long long ll;

const int MAXN = 100000 + 5;

int n, m;
ll p, a[MAXN];

struct SegmentTreeNode {
    int l, r;
    ll sum, addTag, mulTag;
    SegmentTreeNode *lc, *rc;

    SegmentTreeNode(int l, int r, SegmentTreeNode *lc, SegmentTreeNode *rc)
        : l(l), r(r), sum(0), addTag(0), mulTag(1), lc(lc), rc(rc){};

    void pushUp() { sum = ADD(lc->sum, rc->sum); }

    static SegmentTreeNode *build(int l, int r) {
        SegmentTreeNode *ret;
        if (l == r) {
            ret = new SegmentTreeNode(l, r, NULL, NULL);
            ret->sum = a[l] % p;
        } else {
            int mid = l + (r - l) / 2;
            ret = new SegmentTreeNode(l, r, build(l, mid), build(mid + 1, r));
            ret->pushUp();
        }
        return ret;
    }

    void add(ll d) {
        sum = ADD(sum, MUL((r - l + 1), d));
        addTag = ADD(addTag, d);
    }

    void mul(ll d) {
        sum = MUL(sum, d);
        addTag = MUL(addTag, d);
        mulTag = MUL(mulTag, d);
    }

    void pushDown() {
        if (mulTag != 1) {
            lc->mul(mulTag);
            rc->mul(mulTag);
            mulTag = 1;
        }
        if (addTag) {
            lc->add(addTag);
            rc->add(addTag);
            addTag = 0;
        }
    }

    void modifyAdd(int left, int right, ll d) {
        if (left == l && right == r) {
            add(d);
            return;
        }
        pushDown();
        int mid = l + (r - l) / 2;
        if (right <= mid) {
            lc->modifyAdd(left, right, d);
        } else if (left > mid) {
            rc->modifyAdd(left, right, d);
        } else {
            lc->modifyAdd(left, mid, d);
            rc->modifyAdd(mid + 1, right, d);
        }
        pushUp();
    }

    void modifyMul(int left, int right, ll d) {
        if (left == l && right == r) {
            mul(d);
            return;
        }
        pushDown();
        int mid = l + (r - l) / 2;
        if (right <= mid) {
            lc->modifyMul(left, right, d);
        } else if (left > mid) {
            rc->modifyMul(left, right, d);
        } else {
            lc->modifyMul(left, mid, d);
            rc->modifyMul(mid + 1, right, d);
        }
        pushUp();
    }

    ll query(int left, int right) {
        if (left == l && right == r) {
            return sum % p;
        }
        pushDown();
        int mid = l + (r - l) / 2;
        if (right <= mid) {
            return lc->query(left, right);
        } else if (left > mid) {
            return rc->query(left, right);
        } else {
            return ADD(lc->query(left, mid), rc->query(mid + 1, right));
        }
    }
} * root;

int main() {
#ifndef ONLINE_JUDGE
    freopen("data/P2023.in", "r", stdin);
    freopen("data/P2023.out", "w", stdout);
#endif
    scanf("%d %lld", &n, &p);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    root = SegmentTreeNode::build(1, n);
    scanf("%d", &m);
    for (int i = 1, op, l, r, c; i <= m; ++i) {
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1) {
            scanf("%d", &c);
            root->modifyMul(l, r, c);
        } else if (op == 2) {
            scanf("%d", &c);
            root->modifyAdd(l, r, c);
        } else {
            printf("%lld\n", (root->query(l, r) + p) % p);
        }
    }
    return 0;
}
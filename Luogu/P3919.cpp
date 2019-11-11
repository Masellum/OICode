#include <algorithm>
#include <cstdio>

const int MAXN = 1000000 + 5;

int n, m;
int a[MAXN];

struct PST {
#define mid ((l + r) >> 1)
    int root[MAXN], lc[MAXN << 5], rc[MAXN << 5], val[MAXN << 5], tail;

    void build(int &rt, int l, int r) {
        rt = ++tail;
        if (l == r) {
            val[rt] = a[l];
            return;
        }
        build(lc[rt], l, mid);
        build(rc[rt], mid + 1, r);
    }

    void modify(int former, int &rt, int l, int r, int x, int d) {
        if (l == r) {
            val[rt] = d;
            return;
        }
        if (x <= mid) rc[rt] = rc[former], modify(lc[former], lc[rt] = ++tail, l, mid, x, d);
        else lc[rt] = lc[former], modify(rc[former], rc[rt] = ++tail, mid + 1, r, x, d);
    }

    int query(int rt, int l, int r, int x) {
        if (l == r) return val[rt];
        if (x <= mid) return query(lc[rt], l, mid, x);
        else return query(rc[rt], mid + 1, r, x);
    }
#undef mid
} seg;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    seg.build(seg.root[0], 1, n);
    for (int i = 1, v, opt, loc, val; i <= m; ++i) {
        scanf("%d %d %d", &v, &opt, &loc);
        if (opt == 1) {
            scanf("%d", &val);
            seg.modify(seg.root[v], seg.root[i] = ++seg.tail, 1, n, loc, val);
        } else {
            printf("%d\n", seg.query(seg.root[i] = seg.root[v], 1, n, loc));
        }
    }
    return 0;
}
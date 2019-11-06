#include <cstdio>
#include <cstring>

const int MAXQ = 300000 + 5;

int n, q;

template <class T>
void read(T &x) {
    x = 0;
    register char c = getchar();
    while ('0' > c || '9' < c) c = getchar();
    while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = getchar();
}

struct SegmentTree {
#define mid ((l + r) >> 1)
    int root, tail, lc[MAXQ * 50], rc[MAXQ * 50], sum[MAXQ * 50], tag[MAXQ * 50];

    SegmentTree() { memset(tag, 0xff, sizeof(tag)); }

    void cover(int &rt, int l, int r, int d) {
        if (!rt) rt = ++tail;
        sum[rt] = (r - l + 1) * d;
        tag[rt] = d;
    }

    void pushDown(int rt, int l, int r) {
        if (tag[rt] != -1) {
            cover(lc[rt], l, mid, tag[rt]);
            cover(rc[rt], mid + 1, r, tag[rt]);
            tag[rt] = -1;
        }
    }
    
    void add(int &rt, int l, int r, int left, int right, int d) {
        if (!rt) rt = ++tail;
        if (l == left && r == right) {
            cover(rt, l, r, d);
            return;
        }
        pushDown(rt, l, r);
        if (right <= mid) add(lc[rt], l, mid, left, right, d);
        else if (left > mid) add(rc[rt], mid + 1, r, left, right, d);
        else add(lc[rt], l, mid, left, mid, d), add(rc[rt], mid + 1, r, mid + 1, right, d);
        sum[rt] = sum[lc[rt]] + sum[rc[rt]];
    }
#undef mid
} seg;

int main() {
    read(n), read(q);
    for (int i = 1, opt, l, r; i <= q; ++i) {
        read(l), read(r), read(opt);
        seg.add(seg.root, 1, n, l, r, opt & 1);
        printf("%d\n", n - seg.sum[1]);
    }
    return 0;
}
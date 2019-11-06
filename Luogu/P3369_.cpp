#include <algorithm>
#include <cstdio>

char buf[1 << 20], *p1, *p2;

#ifndef _LOCAL
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
#else
#define gc() getchar()
#endif

template <typename T>
void read(T &x) {
    x = 0;
    register bool t = false;
    register char c = gc();
    while ('0' > c || '9' < c) { t = (c == '-'); c = gc(); }
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = gc();
    if (t) x = -x;
}

const int MAXN = 100000 + 5, MAX = 1e7 + 1;

int n;

struct SegmentTree {
#define mid ((l + r) >> 1)
    int root, lc[MAXN << 5], rc[MAXN << 5], sum[MAXN << 5], tail;
    
    void add(int &rt, int l, int r, int x, int d) {
        if (!rt) rt = ++tail;
        sum[rt] += d;
        if (l == r) return;
        if (x <= mid) add(lc[rt], l, mid, x, d);
        else add(rc[rt], mid + 1, r, x, d);
    }

    int s(int rt, int l, int r, int rg) {
        if (r < rg) return sum[rt];
        if (l >= rg) return 0;
        return s(lc[rt], l, mid, rg) + s(rc[rt], mid + 1, r, rg);
    }

    int kth(int rt, int l, int r, int k) {
        if (l == r) return l;
        if (sum[lc[rt]] >= k) return kth(lc[rt], l, mid, k);
        else return kth(rc[rt], mid + 1, r, k - sum[lc[rt]]);
    }

    void insert(int x) { add(root, -MAX, MAX, x, 1); }
    void erase(int x) { add(root, -MAX, MAX, x, -1); }
    int rank(int x) { return s(root, -MAX, MAX, x) + 1; }
    int kth(int k) { return kth(root, -MAX, MAX, k); }
    int pre(int x) { return kth(root, -MAX, MAX, rank(x) - 1); }
    int suc(int x) { return kth(root, -MAX, MAX, rank(x + 1)); }
#undef mid
} seg;

int main() {
    read(n);
    for (int i = 1, opt, x; i <= n; ++i) {
        read(opt), read(x);
        switch (opt) {
            case 1: 
                seg.insert(x);
                break;
            case 2: 
                seg.erase(x);
                break;
            case 3: 
                printf("%d\n", seg.rank(x));
                break;
            case 4: 
                printf("%d\n", seg.kth(x));
                break;
            case 5: 
                printf("%d\n", seg.pre(x));
                break;
            case 6: 
                printf("%d\n", seg.suc(x));
                break;
        }
    }
    return 0;
}
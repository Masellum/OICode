#include <algorithm>
#include <cctype>
#include <cstdio>

const int MAXN = 100000 + 5;

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

int n, m, q, fa[MAXN], id[MAXN], root[MAXN];

struct SegmentTree {
#define mid ((l + r) >> 1)
    int root, lc[MAXN << 6], rc[MAXN << 6], sum[MAXN << 6], tail;
    
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
        if (k > sum[rt]) return 0;
        if (l == r) return l;
        if (sum[lc[rt]] >= k) return kth(lc[rt], l, mid, k);
        else return kth(rc[rt], mid + 1, r, k - sum[lc[rt]]);
    }

    int merge(int u, int v, int l, int r) {
        if (!u || !v) return u + v;
        if (l == r) {
            sum[u] += sum[v];
            return u;
        }
        lc[u] = merge(lc[u], lc[v], l, mid);
        rc[u] = merge(rc[u], rc[v], mid + 1, r);
        sum[u] = sum[lc[u]] + sum[rc[u]];
        return u;
    }
#undef mid
} seg;

int find(int x) {
    return (fa[x] == x ? x : fa[x] = find(fa[x]));
}

void join(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (x > y) std::swap(x, y);
    fa[x] = y;
    seg.merge(root[y], root[x], 1, n);
}

int main() {
    read(n), read(m);
    id[0] = -1;
    for (int i = 1, x; i <= n; ++i) {
        read(x);
        seg.add(root[i], 1, n, x, 1);
        id[x] = i;
        fa[i] = i;
    }
    for (int i = 1, a, b; i <= m; ++i) {
        read(a), read(b);
        join(a, b);
    }
    read(q);
    for (int i = 1, a, b; i <= q; ++i) {
        char c = gc();
        while (!isupper(c)) c = gc();
        if (c == 'Q') {
            read(a), read(b);
            a = find(a);
            printf("%d\n", id[seg.kth(root[a], 1, n, b)]);
        } else {
            read(a), read(b);
            join(a, b);
        }
    }
    return 0;
}
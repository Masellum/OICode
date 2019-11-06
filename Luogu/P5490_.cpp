#include <algorithm>
#include <cstdio>

char buf[1 << 20], *p1, *p2;

#ifndef _LOCAL
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
#else
#define gc() getchar()
#endif

const int MAXN = 100000 + 5;

template <typename T>
void read(T &x) {
    x = 0;
    register char c = gc();
    while ('0' > c || c > '9') c = gc();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = gc();
}

int n;
long long ans;

struct Segment {
    int x, y1, y2, k;
    Segment() {}
    Segment(int x, int y1, int y2, int k) : x(x), y1(y1), y2(y2), k(k) {}

    bool operator<(const Segment &that) const {
        return x < that.x;
    }
} segs[2 * MAXN];

struct SegmentTreeNode {
    int root, ll, rr, lc[MAXN << 6], rc[MAXN << 6], cnt[MAXN << 6], tot;
    long long len[MAXN << 6];

    SegmentTreeNode() : ll(0x7fffffff) {}

    inline void update(int rt, int l, int r) {
        len[rt] = (cnt[rt] > 0 ? r - l + 1 : len[lc[rt]] + len[rc[rt]]);
    }

    void add(int &rt, int l, int r, int left, int right, int k) {
        if (!rt) rt = ++tot;
        if (l == left && r == right) {
            cnt[rt] += k;
            update(rt, l, r);
            return;
        }
        int mid = (l + r) / 2;
        if (right <= mid) {
            add(lc[rt], l, mid, left, right, k);
        } else if (left > mid) {
            add(rc[rt], mid + 1, r, left, right, k);
        } else {
            add(lc[rt], l, mid, left, mid, k);
            add(rc[rt], mid + 1, r, mid + 1, right, k);
        }
        update(rt, l, r);
    }

    void add(int l, int r, int d) {
        add(root, ll, rr - 1, l, r, d);
    }
} seg;

int main() {
    read(n);
    for (int i = 1, x1, y1, x2, y2; i <= n; ++i) {
        read(x1), read(y1), read(x2), read(y2);
        segs[2 * i - 1] = Segment(x1, y1, y2, 1);
        segs[2 * i] = Segment(x2, y1, y2, -1);
        seg.ll = std::min(seg.ll, y1);
        seg.rr = std::max(seg.rr, y2);
    }
    n = 2 * n;
    std::sort(segs + 1, segs + n + 1);
    for (int i = 1; i <= n; ++i) {
        ans += (segs[i].x - segs[i - 1].x) * seg.len[seg.root];
        seg.add(segs[i].y1, segs[i].y2 - 1, segs[i].k);
        // ans += (segs[i + 1].x - segs[i].x) * seg.len[seg.root];
    }
    printf("%lld", ans);
    return 0;
}
#include <algorithm>
#include <cstdio>

#define LC (root * 2)
#define RC (root * 2 + 1) 

typedef long long ll;

const int MAXN = 100000 + 5;

struct Segment {
    int x, y1, y2, k;

    Segment() {}
    Segment(int x, int y1, int y2, int k) : x(x), y1(y1), y2(y2), k(k) {}

    bool operator<(const Segment &that) const {
        return x == that.x ? k > that.k : x < that.x;
    }
} segment[2 * MAXN];

int n;
int rawy[2 * MAXN], ycnt;
ll ans;

struct SegmentTree {
    ll len[MAXN * 8];
    int cnt[MAXN * 8];

    void pushUp(int root, int l, int r) {
        len[root] = cnt[root] ? rawy[r + 1] - rawy[l] : (l == r ? 0 : len[LC]) + (l == r ? 0 : len[RC]);
    }

    void add(int root, int l, int r, int left, int right, int d) {
        if (l == left && r == right) {
            cnt[root] += d;
            return pushUp(root, l, r);
        }
        int mid = (l + r) / 2;
        if (right <= mid) add(LC, l, mid, left, right, d);
        else if (left > mid) add(RC, mid + 1, r, left, right, d);
        else {
            add(LC, l, mid, left, mid, d);
            add(RC, mid + 1, r, mid + 1, right, d);
        }
        pushUp(root, l, r);
    }
} segT;

int main() {
    scanf("%d", &n);
    for (int i = 1, x1, y1, x2, y2; i <= n; ++i) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        segment[2 * i - 1] = Segment(x1, y1, y2, 1);
        segment[2 * i] = Segment(x2, y1, y2, -1);
        rawy[2 * i - 1] = y1;
        rawy[2 * i] = y2;
    }
    std::sort(segment + 1, segment + 2 * n + 1);
    std::sort(rawy + 1, rawy + 2 * n + 1);
    ycnt = std::unique(rawy + 1, rawy + 2 * n + 1) - (rawy + 1);
    for (int i = 1; i <= 2 * n; ++i) {
        segment[i].y1 = std::lower_bound(rawy + 1, rawy + ycnt + 1, segment[i].y1) - rawy;
        segment[i].y2 = std::lower_bound(rawy + 1, rawy + ycnt + 1, segment[i].y2) - rawy;
    }
    for (int i = 1; i < 2 * n; ++i) {
        segT.add(1, 1, ycnt - 1, segment[i].y1, segment[i].y2 - 1, segment[i].k);
        ans += 1ll * (segment[i + 1].x - segment[i].x) * segT.len[1];
    }
    printf("%lld\n", ans);
    return 0;
}
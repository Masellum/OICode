#include <algorithm>
#include <cstdio>

const int MAXN = 200000, MAXNN = 3600000;

int n, m, size, raw[MAXN], arr[MAXN];

struct PST {
    int root[MAXN], lc[MAXNN], rc[MAXNN], sum[MAXNN];
    int tail;

    int build(int l, int r) {
        if (l == r) {
            return ++tail;
        }
        int rt = ++tail, mid = (l + r) / 2;
        lc[rt] = build(l, mid);
        rc[rt] = build(mid + 1, r);
        return rt;
    }

    int add(int former, int l, int r, int val) {
        int rt = ++tail;
        lc[rt] = lc[former];
        rc[rt] = rc[former];
        sum[rt] = sum[former] + 1;
        if (l >= r) return rt;
        int mid = (l + r) / 2;
        if (val <= mid) lc[rt] = add(lc[rt], l, mid, val);
        else rc[rt] = add(rc[rt], mid + 1, r, val);
        return rt;
    }

    int query(int left, int right, int l, int r, int k) {
        if (l >= r) return raw[l];
        int lsize = sum[lc[right]] - sum[lc[left]], mid = (l + r) / 2;
        if (k <= lsize) return query(lc[left], lc[right], l, mid, k);
        else return query(rc[left], rc[right], mid + 1, r, k - lsize);
    }

    int query(int left, int right, int k) {
        return query(root[left - 1], root[right], 1, size, k);
    }

    void build() {
        root[0] = build(1, size);
        for (int i = 1; i <= n; ++i) {
            root[i] = add(root[i - 1], 1, size, arr[i]);
        }
    }
} seg;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", raw + i);
    }
    std::copy(raw + 1, raw + n + 1, arr + 1);
    std::sort(raw + 1, raw + n + 1);
    size = std::unique(raw + 1, raw + n + 1) - (raw + 1);
    for (int i = 1; i <= n; ++i) {
        arr[i] = std::lower_bound(raw + 1, raw + size + 1, arr[i]) - raw;
    }
    seg.build();
    for (int i = 1, l, r, k; i <= m; ++i) {
        scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", seg.query(l, r, k));
    }
    return 0;
}
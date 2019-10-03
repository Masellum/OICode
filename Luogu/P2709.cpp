#include <algorithm>
#include <cmath>
#include <cstdio>

#define sq(x) ((x) * (x))

const int MAXN = 50000 + 5;

int n, m, k, a[MAXN];
int b, s, l = 1, r, ans[MAXN], cnt[MAXN];

struct Q {
    int id, l, r, ans;

    Q() {}
    Q(int id, int l, int r) : id(id), l(l), r(r), ans(0) {}

    bool operator<(const Q &that) const {
        return l / b == that.l / b ? r < that.r : l < that.l;
    }
} q[MAXN];

void add(int x) { s -= sq(cnt[a[x]]); cnt[a[x]]++; s += sq(cnt[a[x]]); }
void del(int x) { s -= sq(cnt[a[x]]); cnt[a[x]]--; s += sq(cnt[a[x]]); }

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 1, l, r; i <= m; ++i) {
        scanf("%d %d", &l, &r);
        q[i] = Q(i, l, r);
    }
    b = sqrt(n);
    std::sort(q + 1, q + m + 1);
    for (int i = 1; i <= m; ++i) {
        while (l > q[i].l) add(--l);
        while (l < q[i].l) del(l++);
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        ans[q[i].id] = s;
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}
#include <algorithm>
#include <cmath>
#include <cstdio>

const int MAXN = 100000 + 5;

int n, q, b, a[MAXN];
int s, l = 1, r, ans[MAXN], cnt[MAXN];

struct Query {
    int l, r, id;

    bool operator<(const Query that) const {
        return l / b == that.l / b ? r < that.r : l < that.l;
    }
} query[MAXN];

void add(int x) { s += (++cnt[a[x]] == 2); }
void del(int x) { s -= (--cnt[a[x]] == 1); }

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= q; ++i) {
        scanf("%d %d", &query[i].l, &query[i].r);
        query[i].id = i;
    }
    b = sqrt(n);
    std::sort(query + 1, query + q + 1);
    for (int i = 1; i <= q; ++i) {
        while (l > query[i].l) add(--l);
        while (l < query[i].l) del(l++);
        while (r < query[i].r) add(++r);
        while (r > query[i].r) del(r--);
        ans[query[i].id] = s;
    }
    for (int i = 1; i <= q; ++i) {
        puts(ans[i] ? "No" : "Yes");
    }
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>

#define lb(x) ((x) & (-(x)))

const int MAXN = 100000 + 5, MOD = 99999997;

int n, a[MAXN], b[MAXN], ia[MAXN], ib[MAXN], fin[MAXN], ans;
int tree[MAXN];

void modify(int x) {
    for (; x <= n; x += lb(x)) {
        tree[x]++;
    }
}

int query(int x) {
    int ret = 0;
    for (; x; x -= lb(x)) {
        ret += tree[x];
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", b + i);
    }
    std::iota(ia + 1, ia + n + 1, 1);
    std::iota(ib + 1, ib + n + 1, 1);
    std::sort(ia + 1, ia + n + 1,
              [](const int &i, const int &j) -> bool { return a[i] < a[j]; });
    std::sort(ib + 1, ib + n + 1,
              [](const int &i, const int &j) -> bool { return b[i] < b[j]; });
    for (int i = 1; i <= n; ++i) {
        fin[ia[i]] = ib[i];
    }
    for (int i = 1; i <= n; ++i) {
        modify(fin[i]);
        ans = (ans + (query(n) - query(fin[i]) % MOD)) % MOD;
    }
    printf("%d", ans);
    return 0;
}
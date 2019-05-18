#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <numeric>
#include <utility>

#define index(x) ((std::lower_bound(raw + 1, raw + size + 1, (x))) - raw)

typedef std::pair<int, int> Pi;

const int MAXN = 100000 + 5;

int fa[2 * MAXN], rank[2 * MAXN], raw[2 * MAXN], n, t, cnt;
Pi eq[MAXN], neq[MAXN];
int eqcnt, neqcnt;

int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (rank[x] > rank[y])
            std::swap(x, y);
        if (rank[x] < rank[y])
            fa[x] = y;
        else {
            if (rand() % 2 > 1) {
                fa[x] = y;
                rank[y]++;
            } else {
                fa[y] = x;
                rank[x]++;
            }
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(rank, 0, sizeof(rank));
        memset(raw, 0, sizeof(raw));
        memset(eq, 0, sizeof(eq));
        memset(neq, 0, sizeof(neq));
        cnt = eqcnt = neqcnt = 0;
        int x, y, e;
        for (int i = 1; i <= n; ++i) {
            scanf("%d %d %d", &x, &y, &e);
            if (e) {
                eq[++eqcnt] = std::make_pair(x, y);
                raw[++cnt] = x;
                raw[++cnt] = y;
            } else {
                neq[++neqcnt] = std::make_pair(x, y);
                raw[++cnt] = x;
                raw[++cnt] = y;
            }
        }
        std::sort(raw + 1, raw + cnt + 1);
        int size = std::unique(raw + 1, raw + cnt + 1) - raw - 1;
        std::iota(fa + 1, fa + size + 1, 1);
        for (int i = 1; i <= eqcnt; ++i) {
            merge(index(eq[i].first), index(eq[i].second));
        }
        bool flag = false;
        for (int i = 1; i <= neqcnt; ++i) {
            if (find(index(neq[i].first)) == find(index(neq[i].second))) {
                puts("NO");
                flag = true;
                break;
            }
        }
        if (!flag) {
            puts("YES");
            continue;
        }
    }
    return 0;
}
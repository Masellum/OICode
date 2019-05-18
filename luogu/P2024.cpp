#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MAXN = 50000 + 5;

int fa[MAXN], d[MAXN], n, k, ans;

int find(int x) {
    if (x == fa[x])
        return x;
    else {
        int f = fa[x];
        fa[x] = find(fa[x]);
        d[x] = (d[x] + d[f]) % 3;
        return fa[x];
    }
}

int main() {
    freopen("testdata/P2024.in", "r", stdin);
    scanf("%d %d", &n, &k);
    int p, x, y, a, b;
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    for (int i = 1; i <= k; ++i) {
        scanf("%d %d %d", &p, &x, &y);
        if (x > n || y > n || (p == 2 && x == y)) {
            ans++;
            continue;
        }
        a = find(x);
        b = find(y);
        if (a == b) {
            if (d[x] != ((d[y] - (p - 1) + 3) % 3)) {
                ans++;
                continue;
            }
        } else {
            fa[b] = a;
            d[b] = ((p - 1) + d[x] - d[y] + 3) % 3;
        }
   }
    printf("%d", ans);
    return 0;
}
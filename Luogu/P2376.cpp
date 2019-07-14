#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

const int MAXN = 20 + 1;

struct Coin {
    int v, b;
} coins[MAXN];

int n, c, k, sum, r, v[MAXN];

int main() {
    scanf("%d %d", &n, &c);
    for (int i = 1, x, y; i <= n; ++i) {
        scanf("%d %d", &x, &y);
        if (x >= c) {
            sum += y;
            continue;
        }
        coins[++k].v = x;
        coins[k].b = y;
    }
    std::sort(coins + 1, coins + k + 1, [](const Coin &a, const Coin &b) -> bool {
        return a.v > b.v;
    });
    while (true) {
        int x = c, ans = INT_MAX;
        memset(v, 0, sizeof(v));
        for (int i = 1; i <= k; ++i) {
            if (coins[i].b <= 0 || coins[i].v >= c) continue;
            if (coins[i].b >= x / coins[i].v) {
                v[i] += x / coins[i].v;
                x %= coins[i].v;
            } else {
                v[i] += coins[i].b;
                x -= coins[i].v * coins[i].b;
            }
        }
        for (int i = k; i >= 1; --i) {
            if (x <= 0) break;
            if (coins[i].b <= v[i] || x > coins[i].v) continue;
            x -= coins[i].v;
            v[i]++;
        }
        if (x > 0) break;
        for (int i = 1; i <= k; ++i) {
            if (v[i]) ans = std::min(ans, coins[i].b / v[i]);
        }
        for (int i = 1; i <= k; ++i) {
            coins[i].b -= ans * v[i];
        }
        sum += ans;
    }
    printf("%d", sum);
    return 0;
}
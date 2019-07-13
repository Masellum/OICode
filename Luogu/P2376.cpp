#include <cstdio>
#include <algorithm>

const int MAXN = 20 + 1;

struct Coin {
    int v, b;
} coins[MAXN];

int n, c, ans, r;

int main() {
    scanf("%d %d", &n, &c);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &coins[i].v, &coins[i].b);
    }
    std::sort(coins + 1, coins + n + 1, [](const Coin &a, const Coin &b) -> bool {
        return a.v > b.v;
    });
    for (int i = 1, now = 0; i <= n; ++i) {
        if (coins[i].v > c) {
            ans += coins[i].b;
            continue;
        }
        r = c % coins[i].v;
        coins[i].b -= c / coins[i].v;
        for (int j = n; j >= i; --j) {
            if (coins[j].b == 0) continue;
            if (coins[j].v * coins[i].b <= r) {
                r -= coins[j].v * coins[i].b;
                coins[i].b = 0;
                continue;
            }
            while (coins[j].b > 0 && r > 0) {
                r -= coins[i].v;
                coins[i].b--;
                
            }
        }
        while (now + coins[i].v <= c) {

        }
    }
}
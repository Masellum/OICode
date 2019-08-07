#include <algorithm>
#include <cmath>
#include <cstdio>

const int MAXN = 1000 + 5;

int n, ans;
double d;

struct Island {
    double l, r;

    bool operator<(const Island that) const {
        return r == that.r ? l < that.l : r < that.r;
    }
} island[MAXN];

int main() {
    scanf("%d %lf", &n, &d);
    for (int i = 1, x, y; i <= n; ++i) {
        scanf("%d %d", &x, &y);
        if (y > d) {
            puts("-1");
            return 0;
        }
        double len = sqrt(d * d - y * y);
        island[i].l = x - len;
        island[i].r = x + len;
    }
    std::sort(island + 1, island + n + 1);
    int now = island[1].r;
    ans = 1;
    for (int i = 2; i <= n; ++i) {
        if (island[i].l > now) {
            now = island[i].r;
            ans++;
        }
    }
    printf("%d", ans);
    return 0;
}
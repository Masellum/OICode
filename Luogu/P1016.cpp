#include <algorithm>
#include <cstdio>

const int MAXN = 6 + 3, INF = 0x3f3f3f3f;

double d1, c, d2, p, ans, rest;
int n, now;

struct Gas {
    double d, p;

    bool operator<(const Gas &that) const {
        return d < that.d;
    }
} gas[MAXN];

int getNext(int now) {
    double d = gas[now].d;
    int minFlag = INF;
    for (int i = now + 1; i <= n + 1 && gas[i].d - d <= c * d2; ++i) {
        if (gas[i].p < gas[now].p) {
            ans += (gas[i].d - d - rest) / d2 * gas[now].p;
            rest = 0;
            return i;
        }
        if (minFlag == INF || gas[i].p < gas[minFlag].p) {
            minFlag = i;
        }
    }
    if (d1 - d <= c * d2) {
        ans += (d1 - gas[now].d - rest) / d2 * gas[now].p;
        return INF;
    }
    if (minFlag == INF) {
        return -1;
    }
    ans += c * gas[now].p;
    rest += (c * d2 - (gas[minFlag].d - gas[now].d));
    return minFlag;
}

int main() {
    scanf("%lf %lf %lf %lf %d", &d1, &c, &d2, &p, &n);
    gas[1].d = 0;
    gas[1].p = p;
    for (int i = 2; i <= n + 1; ++i) {
        scanf("%lf %lf", &gas[i].d, &gas[i].p);
    }
    std::sort(gas + 1, gas + n + 2);
    int now = 1, next;
    do {
        next = getNext(now);
        if (next == -1) {
            puts("No Solution");
            return 0;
        }
        now = next;
    } while (now != INF);
    printf("%.2f", ans);
    return 0;
}
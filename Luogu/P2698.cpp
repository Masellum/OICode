#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

const int MAXD = 1000000 + 5, MAXN = 100000 + 5;

struct Drop {
    int x, y;
} drops[MAXN];

int n, d;
int maxQueue[MAXN], maxHead, maxTail, minQueue[MAXN], minHead, minTail, ans = INT_MAX;

bool check(int w) {
    memset(minQueue, 0, sizeof(minQueue));
    memset(maxQueue, 0, sizeof(maxQueue));
    maxHead = maxTail = minHead = minTail = 0;
    minQueue[minTail++] = maxQueue[maxTail++] = 1;
    if (drops[maxQueue[maxHead]].y - drops[minQueue[minHead]].y >= d) return true;
    for (int i = 2; i <= n; ++i) {
        while (drops[i].y >= drops[maxQueue[maxTail - 1]].y && maxTail > maxHead) {
            maxTail--;
        }
        maxQueue[maxTail++] = i;
        while (drops[maxQueue[maxTail - 1]].x - drops[maxQueue[maxHead]].x > w) {
            maxHead++;
        }
        while (drops[i].y <= drops[minQueue[minTail - 1]].y && minTail > minHead) {
            minTail--;
        }
        minQueue[minTail++] = i;
        while (drops[minQueue[minTail - 1]].x - drops[minQueue[minHead]].x > w) {
            minHead++;
        }
        if (drops[maxQueue[maxHead]].y - drops[minQueue[minHead]].y >= d) return true;
    }
    return false;
}

int main() {
    scanf("%d %d", &n, &d);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &drops[i].x, &drops[i].y);
    }
    std::sort(drops + 1, drops + n + 1, [](const Drop &a, const Drop &b) -> bool {
        return a.x < b.x;
    });
    int minLen = INT_MAX;
    for (int i = 2; i <= n; ++i) {
        minLen = std::min(minLen, drops[i].x - drops[i - 1].x);
    }
    int l = minLen, r = drops[n].x - drops[1].x + 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d", ans == INT_MAX ? -1 : ans);
    return 0;
}

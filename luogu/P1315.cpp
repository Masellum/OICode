#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 1000 + 5, MAXM = 10000 + 5;

struct People {
    int t, l, r;
    People() {}
    People(int t, int l, int r) : t(t), l(l), r(r) {}
} people[MAXM];

int n,
    m, k, length[MAXN], lastArrival[MAXN], count[MAXN], setoff[MAXN], arrive[MAXN], cnt,
    raw[2 * MAXM], ans;
// length[i] 表示以从 i 到 i + 1 所用的时间，
// lastArrival[i] 表示到达第 i 个点的最早时间，
// count[i] 表示从 i 到 i + 1 这段路有几个人搭车，
// setoff[i] 表示实际~~到达第 i 个点~~从第 i 个点出发的时间，
// arrive[i] 表示实际到达第 i 个点的时间，
// raw[i] 表示从 raw[i] 到 raw[i + 1] 这段路有几个人搭车。

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1315_2.in", "r", stdin);
#endif
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &length[i]);
    }
    int t, l, r;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &t, &l, &r);
        people[i] = People(t, l, r);
        lastArrival[l] = std::max(lastArrival[l], t);
        count[l]++;
        count[r]--;
    }
    for (int i = 1; i <= n; ++i) {
        count[i] = count[i - 1] + count[i];
        raw[i] = i;
    }
    std::sort(raw + 1, raw + n, [](const int &a, const int b) -> bool {
        return count[a] > count[b];
    });
    arrive[1] = 0;
    setoff[1] = lastArrival[1];
    for (int i = 2; i <= n; ++i) {
        arrive[i] = setoff[i - 1] + length[i - 1];
        setoff[i] = std::max(lastArrival[i], arrive[i]);
    }
    for (int i = 1; i < n; ++i) {
        if (k == 0) {
            break;
        }
        int idx = raw[i];
        while (/*setoff[idx + 1] > lastArrival[idx + 1] && */length[idx] > 0 &&
               k > 0) {
            k--;
            arrive[idx + 1]--;
            length[idx]--;
        }
        for (int j = idx + 1; j <= n; ++j) {
            arrive[j] = setoff[j - 1] + length[j - 1];
            setoff[j] = std::max(lastArrival[j], arrive[j]);
        }
    }
    for (int i = 1; i <= m; ++i) {
        ans += arrive[people[i].r] - people[i].t;
    }
    printf("%d\n", ans);
    return 0;
}
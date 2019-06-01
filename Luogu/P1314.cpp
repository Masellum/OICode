#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

const int MAX = 200000 + 5;

typedef long long ll;

struct Range {
    int l, r;
    Range() {}
    Range(int l, int r) : l(l), r(r) {}
} range[MAX];

int n, m, w[MAX], v[MAX], W, minw = INT_MAX, maxw = INT_MIN;
ll s, sum = 0;
ll sumw[MAX], sumv[MAX];

inline ll llabs(ll x) { return x > 0 ? x : -x; }

void check() {
    memset(sumv, 0, sizeof(sumv));
    memset(sumw, 0, sizeof(sumw));
    for (int i = 1; i <= n; ++i) {
        if (w[i] >= W) {
            sumw[i] = sumw[i - 1] + v[i];
            sumv[i] = sumv[i - 1] + 1;
        } else {
            sumw[i] = sumw[i - 1];
            sumv[i] = sumv[i - 1];
        }
    }
    sum = 0;
    int l, r;
    for (int i = 1; i <= m; ++i) {
        l = range[i].l, r = range[i].r;
        sum += (sumv[r] - sumv[l - 1]) * (sumw[r] - sumw[l - 1]);
    }
}

int main(int argc, char const *argv[]) {
    freopen("testdata/P1314.in", "r", stdin);
    scanf("%d %d %lld", &n, &m, &s);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &w[i], &v[i]);
        minw = std::min(minw, w[i]);
        maxw = std::max(maxw, w[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &range[i].l, &range[i].r);
    }
    int l = minw - 1, r = maxw + 2;
    long long diff = LLONG_MAX;
    while (l < r) {
        W = l + (r - l) / 2;
        check();
        if (sum == s) {
            puts("0");
            return 0;
        } else if (sum < s) {
            r = W;
        } else {
            l = W + 1;
        }
        if (llabs(s - sum) < diff) {
            diff = llabs(s - sum);
        }
    }
    // int l = minw - 1, r = maxw + 2;
    // ll diff = LLONG_MAX;
    // while (l <= r) {
    //     W = (l + r) >> 1;
    //     check();
    //     if (sum > s) {
    //         l = W + 1;
    //     } else {
    //         r = W - 1;
    //     }
    //     if (llabs(sum - s) < diff) {
    //         diff = llabs(sum - s);
    //     }
    // }
    printf("%lld", diff);
    return 0;
}
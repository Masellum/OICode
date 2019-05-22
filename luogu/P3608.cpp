#include <algorithm>
#include <cstdio>

#define lb(x) ((x) & (-(x)))

const int maxn = 100000 + 5;

int n, h[maxn], lh[maxn], rh[maxn], ans;
int raw[maxn];
int left[maxn], right[maxn];

void add(int bit[], int index, int d) {
    for (; index <= n; index += lb(index)) {
        bit[index] += d;
    }
}

int query(int bit[], int index) {
    int ret = 0;
    for (; index; index -= lb(index)) {
        ret += bit[index];
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", raw + i);
    }
    std::copy(raw + 1, raw + n + 1, h + 1);
    std::sort(raw + 1, raw + n + 1);
    for (int i = 1; i <= n; ++i) {
        h[i] = std::lower_bound(raw + 1, raw + n + 1, h[i]) - raw;
    }
    for (int i = 1; i <= n; ++i) {
        add(left, h[i], 1);
        lh[i] = query(left, n) - query(left, h[i]);
    }
    for (int i = n; i >= 1; --i) {
        add(right, h[i], 1);
        rh[i] = query(right, n) - query(right, h[i]);
    }
    for (int i = 1, g, l; i <= n; ++i) {
        if (lh[i] > rh[i]) {
            g = lh[i], l = rh[i];
        } else {
            g = rh[i], l = lh[i];
        }
        if (g > 2 * l) {
            ans++;
        }
    }
    printf("%d", ans);
    return 0;
}
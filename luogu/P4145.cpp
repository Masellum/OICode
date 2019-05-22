#include <algorithm>
#include <cmath>
#include <cstdio>

typedef long long ll;

const int MAXN = 100000 + 5;

int n, m, size, block[MAXN];
ll a[MAXN], sum[MAXN];
bool clean[MAXN];

ll query(int l, int r) {
    ll res = 0;
    for (int i = l; i <= std::min(block[l] * size, r); ++i) {
        res += a[i];
    }
    if (block[l] != block[r]) {
        for (int i = (block[r] - 1) * size + 1; i <= r; ++i) {
            res += a[i];
        }
    }
    for (int i = block[l] + 1; i < block[r]; ++i) {
        res += sum[i];
    }
    return res;
}

void square(int l, int r) {
    for (int i = l; i <= std::min(block[l] * size, r); ++i) {
        sum[block[l]] -= a[i];
        a[i] = ll(sqrt(a[i]));
        sum[block[l]] += a[i];
    }
    if (block[l] != block[r]) {
        for (int i = (block[r] - 1) * size + 1; i <= r; ++i) {
            sum[block[r]] -= a[i];
            a[i] = ll(sqrt(a[i]));
            sum[block[r]] += a[i];
        }
    }
    for (int i = block[l] + 1; i < block[r]; ++i) {
        if (clean[i])
            continue;
        clean[i] = true;
        sum[i] = 0;
        for (int j = (i - 1) * size + 1; j <= i * size; ++j) {
            a[j] = ll(sqrt(a[j]));
            sum[i] += a[j];
            if (a[j] != 0 && a[j] != 1)
                clean[i] = false;
        }
    }
}

int main() {
    scanf("%d", &n);
    size = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
        block[i] = (i - 1) / size + 1;
        sum[block[i]] += a[i];
    }
    scanf("%d", &m);
    for (int i = 1, k, l, r; i <= m; ++i) {
        scanf("%d%d%d", &k, &l, &r);
        if (l > r)
            std::swap(l, r);
        if (k) {
            printf("%lld\n", query(l, r));
        } else {
            square(l, r);
        }
    }
    return 0;
}
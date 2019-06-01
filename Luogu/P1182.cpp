#include <algorithm>
#include <climits>
#include <cstdio>

const int MAXN = 100000 + 5;

int n, m, a[MAXN];

bool check(int maxVal) {
    int cnt = 0, sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (sum + a[i] > maxVal) {
            cnt++;
            sum = 0;
            if (cnt >= m) {
                return false;
            }
        }
        sum += a[i];
    }
    return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1182.in", "r", stdin);
    freopen("testdata/P1182.out", "w", stdout);
#endif
    scanf("%d %d", &n, &m);
    int max = INT_MIN, sum = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        max = std::max(max, a[i]);
        sum += a[i];
    }
    int l = max , r = sum;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d", l);
    return 0;
}
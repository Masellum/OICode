#include <algorithm>
#include <climits>
#include <cstdio>
#include <numeric>

const int MAX = 100000 + 5;

int arr[MAX], a, b, d[MAX];

bool check(int minLen) {
    int cnt = 1, last = arr[1];
    for (int i = 2; i <= a; ++i) {
        if (arr[i] - last - 1 >= minLen) {
            cnt++;
            if (cnt >= b) {
                return true;
            }
            last = arr[i];
        }
    }
    return cnt >= b;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1316.in", "r", stdin);
    freopen("testdata/P1316.out", "w", stdout);
#endif
    scanf("%d %d", &a, &b);
    for (int i = 1; i <= a; ++i) {
        scanf("%d", &arr[i]);
    }
    std::sort(arr + 1, arr + a + 1);
    std::adjacent_difference(arr + 1, arr + a + 1, d + 1);
    int l = *std::min_element(d + 1, d + a + 1), r = arr[a] - arr[1];
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    printf("%d", l);
    return 0;
}
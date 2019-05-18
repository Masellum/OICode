#include <algorithm>
#include <cstdio>

#define lb(x) ((x)&(-(x)))

int n, k, ans;

// int onecnt(int x) {
//     int cnt = 0;
//     for (int i = 0; (1 << i) <= x; ++i) {
//         if ((1 << i) & x) {
//             cnt++;
//         }
//     }
//     return cnt;
// }

int main() {
    scanf("%d %d", &n, &k);
    while (__builtin_popcount(n) > k) {
        ans += lb(n);
        n += lb(n);
    }
    printf("%d", ans);
    return 0;
}
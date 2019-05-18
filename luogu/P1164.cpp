#include <cstdio>
#include <algorithm>

//const int SMALL_ENUF = -2147493648;

int n, m, a[105], dp[10005]; 
//dp[i]表示花了i元钱时的最大菜数
//也就是说，相当于每个菜的cost都是1时的最大价值 

void init() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &(a[i]));
    }
    for (int i = 1; i<= n; ++i) {
        dp[i] = 0;
    }
//    dp[0] = 0;
    dp[0] = 1;
}

int main() {
    init();
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= a[i]; --j) {
            dp[j] += dp[j - a[i]];
        }
    }
    printf("%d", dp[m]);
    return 0;
}

#include <cstdio>
#include <algorithm>

int t, m, time[10005], value[10005], dp[100005];

void init() {
    scanf("%d%d", &t, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &(time[i]), &(value[i]));
    }
}

int main() {
    init();
//    for (int i = 1; i <= m; ++i) {
//        for (int j = time[i]; j <= t; ++j) {
//            for (int k = 1; 0 <= k * time[i] && k * time[i] <= j; k++) {
//                dp[j] = std::max(dp[j], dp[j - k * time[j]] + k * value[j]);
//            }
//        }
//    }
    for (int i = 1; i <= m; ++i) {
        for (int j = time[i]; j <= t; ++j) {
            dp[j] = std::max(dp[j], dp[j - time[i]] + value[i]); 
        }
    }
    printf("%d", dp[t]);
    return 0;
}

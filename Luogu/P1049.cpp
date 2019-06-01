#include <algorithm>
#include <iostream>

int V, n, v[35], dp[20005];

void init() {
    std::cin >> V >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> v[i];
    }
}

int main() {
    init();
    for (int i = 1; i <= n; ++i) {
        for (int j = V; j >= v[i]; --j) {
            dp[j] = std::max(dp[j], dp[j - v[i]] + v[i]);
        }
    }
    std::cout << V - dp[V] << std::endl;
    return 0;
}

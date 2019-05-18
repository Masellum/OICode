#include <algorithm>
#include <cstdio>

const int MAXN = 21;

int x[MAXN], n, k, ans;

bool isPrime(int num) {
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void dfs(int cnt, int sum, int index) {
    if (cnt == k) {
        if (isPrime(sum)) {
            ans++;
        }
    } else {
        for (int i = index; i <= n; ++i) {
            dfs(cnt + 1, sum + x[i], i + 1);
        }
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x[i]);
    }
    dfs(0, 0, 1);
    printf("%d", ans);
    return 0;
}
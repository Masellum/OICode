#include <algorithm>
#include <climits>
#include <cstdio>

const int MAXN = 100000 + 5;

int n, raw[MAXN], sorted[MAXN], pos[MAXN];
int len, min;
long long ans, sum;
bool vis[MAXN];

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    sum += raw[x];
    len++;
    min = std::min(min, raw[x]);
    dfs(pos[x]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", raw + i);
    }
    std::copy(raw + 1, raw + n + 1, sorted + 1);
    std::sort(sorted + 1, sorted + n + 1);
    for (int i = 1; i <= n; ++i) {
        pos[i] = std::lower_bound(sorted + 1, sorted + n + 1, raw[i]) - sorted;
    }
    for (int i = 1; i <= n; ++i) {
        if (raw[i] == sorted[i]) continue;
        if (vis[i]) continue;
        min = INT_MAX;
        sum = len = 0;
        dfs(i);
        ans += std::min(sum + 1ll * (len - 2) * min, sum + min + 1ll * (len + 1) * sorted[1]);
    }
    printf("%lld", ans);
    return 0;
}
#include <cstdio>

const int MAXN = 100000 + 5;

int n, num[MAXN], index[MAXN], ans[MAXN], cnt;
int prev[MAXN], next[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1, val; i <= n; ++i) {
        scanf("%d", num + i);
        prev[num[i]] = num[i - 1];
        next[num[i - 1]] = num[i];
    }
    for (int i = n; i >= 1; --i) {
        if (!next[i]) continue;
        printf("%d %d ", i, next[i]);
        next[prev[i]] = next[next[i]];
        prev[next[next[i]]] = prev[i];
        next[next[i]] = 0;
    }
    return 0;
}
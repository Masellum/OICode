#include <algorithm>
#include <cstdio>

const int MAXN = 10000 + 5;

int n, h[MAXN], ans;
bool low;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", h + i);
    }
    for (int i = 2; i <= n; ++i) {
        if (h[i] < h[i - 1]) low = true;
        else if (h[i] > h[i - 1] && low) { ans++; low = false; }
    }
    printf("%d", ans);
    return 0;
}
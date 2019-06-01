#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXK = 50 + 1;

int lastAppearance[MAXK], countOfColors[MAXK], countOfSolutions[MAXK], lastAvailable, ans;
int n, k, p;

int main() {
    scanf("%d %d %d", &n, &k, &p);
    int color, cost;
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &color, &cost);
        if (cost <= p) {
            lastAvailable = i;
        }
        if (lastAvailable >= lastAppearance[color]) {
            countOfSolutions[color] = countOfColors[color];
        }
        lastAppearance[color] = i;
        ans += countOfSolutions[color];
        countOfColors[color]++;
    }
    printf("%d\n", ans);
    return 0;
}
#include <cstdio>
#include <algorithm>

int n, m, a[100005], cnt, sum;

void init() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &(a[i]));
    }
}

int main() {
    init();
    for (int i = 1; i <= n; i++) {
        sum += a[i];
        if (sum > m) {
            cnt++;
            sum = 0;
            i--;
        }
    }
    printf("%d", cnt + 1);
    return 0;
}


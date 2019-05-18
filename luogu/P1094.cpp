#include <algorithm>
#include <cstdio>

int w, n, p[30005], sum, ans, cnt, head, tail;

void init() {
    scanf("%d%d", &w, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &(p[i]));
    }
    std::sort(p + 1, p + n + 1);
    head = 1;
    tail = n;
}

int main() {
    init();
    while (head <= tail) {
        if (p[head] + p[tail] <= w) {
            ans++;
            head++;
            tail--;
            continue;
        }
        ans++;
        tail--;
    }
    //    if (p[head] + p[tail + 1] <= w) {
    //        printf("%d", ans);
    //    } else {
    //        printf("%d", ans + 1);
    //    }
    printf("%d", ans);
    return 0;
}

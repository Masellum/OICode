#include <algorithm>
#include <climits>
#include <cstdio>

const int MAXN = 1000000 + 5;

int n, m, a[MAXN], q[MAXN], cnt;
int queue[MAXN], index[MAXN], head, tail;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= m; ++i) {
        while (queue[tail - 1] > a[i] && tail != head) {
            tail--;
        }
        index[tail] = i;
        queue[tail++] = a[i];
    }
    q[++cnt] = queue[head];
    for (int i = m + 1; i <= n; ++i) {
        while (queue[tail - 1] > a[i] && tail != head) {
            tail--;
        }
        index[tail] = i;
        if (index[tail] - index[head] >= m) {
            head++;
        }
        queue[tail++] = a[i];
        q[++cnt] = queue[head];
    }
    for (int i = 1; i <= cnt; ++i) {
        printf("%d\n", q[i]);
    }
    return 0;
}
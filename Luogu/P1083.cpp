#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 1000000 + 5;

struct Request {
    int d, s, t;
    Request() {}
    Request(int d, int s, int t) : d(d), s(s), t(t) {}
} request[MAXN];

int n, m;

int a[MAXN];
ll d[MAXN];

bool check(int mid) {
    for (int i = 1; i <= mid; ++i) {
        d[request[i].s] -= request[i].d;
        d[request[i].t + 1] += request[i].d;
    }
    int t = 0;
    for (int i = 1; i <= n; ++i) {
        t += d[i] + a[i] - a[i - 1];
        if (t < 0)
            return false;
    }
    return true;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &request[i].d, &request[i].s, &request[i].t);
    }
    int l = 1, r = m + 1;
    while (l < r) {
        memset(d, 0, sizeof(d));
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if (l >= m) {
        puts("0");
    } else
        printf("-1\n%d", l);
    return 0;
}
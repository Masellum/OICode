#include <bits/stdc++.h>
#define lowb(x) ((x)&(-(x)))

const int MAX = 1000000 + 5;
int n;
int a[MAX], b[MAX], c[MAX];

void add(int x) {
    for (; x <= n; x += lowb(x)) {
        c[x]++;
    }
}

int query(int x) {
    int ans = 0;
    for (; x; x -= lowb(x)) {
        ans += c[x];
    }
    return ans;
}

bool compare(const int &x, const int &y) {
    return b[x] < b[y];
}

int main() {
    int ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &(b[i]));
        a[i] = i;
    }
    std::sort(a + 1, a + n + 1, compare);
    for (int i = 1; i <= n; ++i) {
        add(a[i]);
        ans += query(n) - query(a[i]);
    }
    printf("%d", ans);
    return 0;
}

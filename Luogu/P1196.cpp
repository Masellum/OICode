#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAXN = 30000 + 5;

int fa[MAXN], cnt[MAXN], d[MAXN], t /*  */;

int find(int x) {
    if (x != fa[x]) {
        int k = fa[x];
        fa[x] = find(fa[x]);
        d[x] = d[x] + d[k];
        cnt[x] = cnt[k];
    }
    return fa[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    fa[x] = y;
    d[x] = d[y] + cnt[y];
    cnt[y] += cnt[x];
    cnt[x] = cnt[y];
}

int main() {
    scanf("%d\n", &t);
    for (int i = 1; i <= 30000; ++i) {
        fa[i] = i;
        d[i] = 0;
        cnt[i] = 1;
    }
    char c;
    int x, y;
    while (t--) {
        std::cin >> c >> x >> y;
        if (c == 'M') {
            merge(x, y);
        } else if (c == 'C') {
            int a = find(x), b = find(y);
            if (a != b) {
                printf("-1\n");
                continue;
            } else {
                printf("%d\n", std::abs(d[x] - d[y]) - 1);
            }
        }
    }
    return 0;
}
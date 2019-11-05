#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>

char buf[1 << 20], *p1, *p2;

#ifndef _LOCAL
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
#else
#define gc() getchar()
#endif

const int MAXN = 300000 + 5;

template <typename T>
void read(T &x) {
    x = 0;
    register char c = gc();
    while ('0' > c || '9' < c) c = gc();
    while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = gc();
}

int n, m;
int s[2 * MAXN], root[2 * MAXN], tail;
int son[2 * MAXN * 25][2], cnt[2 * MAXN * 25];

void add(int former, int now, int x, int d) {
    if (d < 0) return;
    int f = (x >> d) & 1;
    son[now][!f] = son[former][!f];
    son[now][f] = ++tail;
    cnt[son[now][f]] = cnt[son[former][f]] + 1;
    add(son[former][f], son[now][f], x, d - 1);
}

int query(int l, int r, int x, int d) {
    if (d < 0) return 0;
    int f = (x >> d) & 1;
    if (cnt[son[r][!f]] > cnt[son[l][!f]])
        return (1 << d) + query(son[l][!f], son[r][!f], x, d - 1);
    else return query(son[l][f], son[r][f], x, d - 1);
}

int main() {
    read(n), read(m);
    add(0, root[0] = ++tail, 0, 23);
    for (int i = 1; i <= n; ++i) {
        read(s[i]);
        s[i] ^= s[i - 1];
        add(root[i - 1], root[i] = ++tail, s[i], 23);
    }
    for (int i = 1, l, r, x; i <= m; ++i) {
        char c = gc();
        while (!isupper(c)) c = gc();
        if (c == 'A') {
            read(s[++n]);
            s[n] ^= s[n - 1];
            add(root[n - 1], root[n] = ++tail, s[n], 23);
        } else {
            read(l), read(r), read(x);
            l -= 1, r -= 1;
            if (l == 0) printf("%d\n", query(0, root[r], x ^ s[n], 23));
            else printf("%d\n", query(root[l - 1], root[r], x ^ s[n], 23));
        }
    }
    return 0;
}
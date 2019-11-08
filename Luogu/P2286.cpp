#include <cmath>
#include <cstdio>
#include <climits>
#include <limits>
#include <set>

const int MAXN = 80000 + 5, MOD = 1000000;

template <class T>
void read(T &x) {
    x = 0;
    register char c = getchar();
    while ('0' > c || '9' < c) c = getchar();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = getchar();
}

// struct SegmentTree {
// #define mid ((l + (r - l) / 2))
//     int s[MAXN << 6], lc[MAXN << 6], rc[MAXN << 6], root, tail;

//     void add(int &rt, int l, int r, int x, int d) {
//         if (!rt) rt = ++tail;
//         s[rt] += d;
//         if (l == r) return;
//         if (x <= mid) add(lc[rt], l, mid, x, d);
//         else add(rc[rt], mid + 1, r, x, d);
//         // s[rt] = s[lc[rt]] + s[rc[rt]];
//     }

//     int sum(int rt, int l, int r, int rg) {
//         if (r < rg) return s[rt];
//         if (l >= rg) return 0;
//         return sum(lc[rt], l, mid, rg) + sum(rc[rt], mid + 1, r, rg);
//     }

//     int kth(int rt, int l, int r, int k) {
//         if (l == r) return l;
//         if (s[lc[rt]] >= k) return kth(lc[rt], l, mid, k);
//         else return kth(rc[rt], mid + 1, r, l - s[lc[rt]]);
//     }

//     void insert(int x) { add(root, 1, INT_MAX, x, 1); }
//     void erase(int x) { add(root, 1, INT_MAX, x, -1); }
//     int rank(int x) { return sum(root, 1, INT_MAX, x) + 1; }
//     int kth(int k) { return kth(root, 1, INT_MAX, k); }
//     int pre(int x) { return kth(root, 1, INT_MAX, rank(x) - 1); }
//     int suc(int x) { return kth(root, 1, INT_MAX, rank(x + 1));}
// #undef mid
// } seg;

int n, ans, last = -1;
bool ins = false;
std::set<int> s;

void find(int x) {
    std::set<int>::iterator left, right;
    left = --s.lower_bound(x), right = s.lower_bound(x);
    if (x - *left <= *right - x && *left != -0x3f3f3f3f) {
        ans = (ans + (x - *left) % MOD) % MOD;
        s.erase(left);
    } else {
        ans = (ans + (*right - x) % MOD) % MOD;
        s.erase(right);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/1208/1.in", "r", stdin);
    freopen("testdata/P2286.out", "w", stdout);
#endif
    read(n);
    s.insert(-0x3f3f3f3f), s.insert(0x3f3f3f3f);
    for (int i = 1, a, b; i <= n; ++i) {
        read(a), read(b);
        // if (last != a || seg.s[seg.root] == 0) ins = !ins;
        if (last != a || s.size() == 2) ins = !ins;
        last = a;
        if (ins) {
            // seg.insert(b);
            s.insert(b);
        } else {
            find(b);
            // if (seg.s[seg.root] == 1) {
            //     ans = (ans + abs(b % MOD - seg.kth(1) % MOD) % MOD) % MOD;
            //     seg.erase(seg.kth(1));
            //     continue;
            // }
            // else {
            //     int p = seg.pre(b), s = seg.suc(b);
            //     if (b - p >= s - b) {
            //         ans = (ans + (b - p) % MOD) % MOD;
            //         seg.erase(p);
            //     } else {
            //         ans = (ans + (s - b) % MOD) % MOD;
            //         seg.erase(s);
            //     }
            // }
        }
    }
    printf("%d\n", (ans + MOD) % MOD);
    return 0;
}
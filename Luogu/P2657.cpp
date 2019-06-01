#include <algorithm>
#include <cstdio>

#define lb(x) ((x) & (-(x)))

const int MAXN = 20000 + 5;

int n, v[MAXN], x[MAXN], ans;
int num[MAXN], sum[MAXN];

void modify(int tree[], int ind, int x) {
    for (; ind <= n; ind += lb(ind)) {
        tree[ind] += x;
    }
}

int query(int tree[], int ind) {
    int res = 0;
    for (; ind; ind -= lb(ind)) {
        res += tree[ind];
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", v + i, x + i);
    }
    std::sort()
}
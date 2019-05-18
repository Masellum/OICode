#include <algorithm>
#include <cstdio>

const int MAX = 1030;

struct Node {
    char type;
} node[MAX];

int n;
char s[MAX];

int dfs(int l, int r) {
    if (l == r) {
        if (s[l] == '0') {
            printf("B");
            return 0;
        } else {
            printf("I");
            return 1;
        }
    }
    int mid = (l + r) / 2;
    int ll = dfs(l, mid), rr = dfs(mid + 1, r);
    if (ll == rr) {
        if (ll == 0) {
            printf("B");
            return 0;
        } else if (ll == 1) {
            printf("I");
            return 1;
        } else {
            printf("F");
            return 2;
        }
    } else {
        printf("F");
        return 2;
    }
}

int main() {
    scanf("%d%s", &n, s + 1);
    if (n == 0) {
        if (s[1] == '0') {
            puts("B");
            return 0;
        } else {
            puts("I");
            return 0;
        }
    }
    dfs(1, 1 << n);
    return 0;
}
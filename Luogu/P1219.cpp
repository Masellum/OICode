#include <algorithm>
#include <cstdio>
#include <cstring>

int n;
int queen[14];
int rowcol[14] = {0};
int pie[14 + 7] = {0}; //以x为准
int na[14 + 7] = {0};  // x-y，有负数所以+7
int cnt = 0;

void print() {
    cnt++;
    if (cnt <= 3) {
        for (int i = 1; i <= n; ++i) {
            printf("%d ", queen[i]);
        }
        printf("\n");
    }
}

void dfs(int sr) {
    for (int i = 1; i <= n; i++) {
        if (!rowcol[i] && !pie[i + sr] && !na[i - sr + 7]) {
            queen[sr] = i;
            rowcol[i] = 1;
            pie[i + sr] = 1;
            na[i - sr + 7] = 1;
            if (sr == n) {
                print();
            } else {
                dfs(sr + 1);
            }
            rowcol[i] = 0;
            pie[i + sr] = 0;
            na[i - sr + 7] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    dfs(1);
    printf("%d", cnt);
    return 0;
}

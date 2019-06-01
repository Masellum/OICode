#include <cstdio>
#include <algorithm>

int n, mat[8][6], count[11];
bool flag;

void dfs(int x, int y, int step) {
    
}

int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for (int i = 1; i <= 5; ++i) {
        int t, cnt = 0;
        scanf("%d", &t);
        while (t != 0) {
            count[t]++;
            mat[++cnt][i] = t;
            scanf("%d", &t);
        }
    }

    return 0;
}
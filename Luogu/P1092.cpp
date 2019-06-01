#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 26 + 1;

int n;
bool used[MAXN];
int num[MAXN];
char s[4][MAXN];

inline int id(char c) { return c - 'A' + 1; }

void dfs(int x, int y, int t) {
    if (y == 0) { // 递归终止条件
        if (t == 0) {
            for (int i = 1; i < n; ++i) {
                printf("%d ", num[i]);
            }
            printf("%d\n", num[n]);
            exit(0);
        } else {
            return;
        }
    }
    for (int i = y - 1; i >= 1; --i) { // 剪枝1
        int n1 = num[id(s[1][i])], n2 = num[id(s[2][i])], n3 = num[id(s[3][i])];
        if (n1 == -1 || n2 == -1 || n3 == -1)
            continue;
        if ((n1 + n2) % n != n3 && (n1 + n2 + 1) % n != n3)
            return;
    }
    if (num[id(s[x][y])] == -1) {
        for (int i = n - 1; i >= 0; --i) {
            if (!used[i]) {
                if (x != 3) {
                    used[i] = true;
                    num[id(s[x][y])] = i;
                    dfs(x + 1, y, t);
                    used[i] = false;
                    num[id(s[x][y])] = -1;
                } else {
                    int sum = num[id(s[1][y])] + num[id(s[2][y])] + t;
                    if (sum % n != i)
                        continue;
                    used[i] = true;
                    num[id(s[x][y])] = i;
                    dfs(1, y - 1, sum / n);
                    used[i] = false;
                    num[id(s[x][y])] = -1;
                }
            }
        }
    } else {
        if (x != 3)
            dfs(x + 1, y, t);
        else {
            int sum = num[id(s[1][y])] + num[id(s[2][y])] + t;
            if (sum % n != num[id(s[x][y])])
                return;
            else {
                dfs(1, y - 1, sum / n);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s%s%s", s[1] + 1, s[2] + 1, s[3] + 1);
    memset(num, -1, sizeof(num));
    dfs(1, n, 0);
    return 0;
}
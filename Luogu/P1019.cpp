#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#define DEBUG(x) std::cerr << #x << "=" << (x) << std::endl

const int MAXN = 20 + 3;

std::string strs[MAXN];
int n, len[MAXN][MAXN], ans = 0;
int vis[MAXN];
char c;

void calc(int x, int y) {
    const std::string &a = strs[x], &b = strs[y];
    int lena = a.length(), lenb = b.length();
    int l = lena - 1;
    bool ok = true;
    while (l >= 0) {
        for (int i = l, j = 0; i < lena && j < lenb; ++i, ++j) {
            if (a[i] != b[j]) {
                ok = false;
                break;
            }
        }
        if (ok && lena - l != lenb && lena - l != lena) {
            len[x][y] = lena - l;
            break;
        }
        l -= 1;
        ok = true;
    }
}

// void dfs(int x, int length) {
//     vis[x]++;
//     ans = std::max(ans, length);
//     for (int i = 1; i <= n; ++i) {
//         if (vis[x] < 2 && len[x][i] > 0) {
//             dfs(i, length - len[x][i] + strs[i].length());
//         }
//     }
//     vis[x]--;
// }

void dfs(int x, int length) {
    ans = std::max(ans, length);
    for (int i = 1; i <= n; i++) {
        if (vis[i] < 2 && len[x][i] > 0) {
            vis[i]++;
            dfs(i, length - len[x][i] + strs[i].length());
            vis[i]--;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("testdata/P1019.in", "r", stdin);
    #endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> strs[i];
    }
    getchar();
    getchar();
    scanf("%c", &c);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
                calc(i, j);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (strs[i].at(0) == c) {
            vis[i]++;
            ans = std::max(ans, int(strs[i].length()));
            dfs(i, strs[i].length());
            vis[i]--;
        }
    }
    printf("%d", ans);
    return 0;
}
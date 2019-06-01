#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXK = 100 + 5, MAXN = 1000 + 5;

char k[MAXK], s[MAXN], ans[MAXN];
int lenk, lens;
bool upper = false;

int main() {
    scanf("%s", k + 1);
    scanf("%s", s + 1);
    lenk = strlen(k + 1);
    lens = strlen(s + 1);
    for (int i = 1, j = 1; i <= lens; ++i) {
        int a, b, c;
        if (j == lenk + 1)
            j = 1;
        if ('A' <= s[i] && s[i] <= 'Z') {
            upper = true;
            a = s[i] - 'A' + 1;
        } else {
            upper = false;
            a = s[i] - 'a' + 1;
        }
        b = k[j] - 'a' + 1, c = (abs(a - b) + 1) % 26;
        ans[i] = c + "aA"[int(upper)] - 1;
        ans[i + 1] = '\0';
    }
    // printf(ans + 1);
    return 0;
}
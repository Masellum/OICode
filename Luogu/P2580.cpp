#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 10000 + 5;

struct TrieNode {
    int count, child[26];
} trieNode[26 * 50 * MAXN];

int n, m, cnt;

void trieInsert(char str[]) {
    int len = strlen(str), now = 0;
    for (int i = 0; i < len; ++i) {
        if (trieNode[now].child[str[i] - 'a'] == 0) {
            trieNode[now].child[str[i] - 'a'] = ++cnt;
        }
        now = trieNode[now].child[str[i] - 'a'];
    }
    trieNode[now].count++;
}

int trieQuery(char str[]) {
    int len = strlen(str), now = 0;
    for (int i = 0; i < len; ++i) {
        now = trieNode[now].child[str[i] - 'a'];
        if (now == 0) return -1;
        // if (trieNode[now].count == 0) return -1;
    }
    return trieNode[now].count;
}

int main() {
    scanf("%d", &n);
    char s[55];
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s);
        trieInsert(s);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%s", s);
        int res = trieQuery(s);
        if (res == -1) {
            puts("WRONG");
        } else if (res > 1) {
            puts("REPEAT");
        } else {
            puts("OK");
            trieInsert(s);
        }
    }
    return 0;
}
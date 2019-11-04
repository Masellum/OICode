#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <queue>

const int MAXN = 500 + 1;
int MAP[90];

int n;
int trie[5 * 500 * MAXN][5], cnt, ans, len;
char tmp[1005], s[MAXN];
std::bitset<2 * MAXN> vis[5 * 500 * MAXN];
std::bitset<5 * 500 * MAXN> term;
// bool vis[5 * 500 * MAXN][2 * MAXN], term[5 * 500 * MAXN];

struct Pair {
    int tnode, ind;
    Pair(int tnode, int ind) : tnode(tnode), ind(ind) {}
};

void insert(char s[]) {
    int now = 0;
    for (int i = 0; s[i]; ++i) {
        now = (trie[now][MAP[int(s[i])]] ? trie[now][MAP[int(s[i])]] : (trie[now][MAP[int(s[i])]] = ++cnt));
    }
    term[now] = true;
}

void bfs() {
    std::queue<Pair> q;
    q.push(Pair(0, 0));
    while (!q.empty()) {
        int u = q.front().tnode, v = q.front().ind;
        q.pop();
        if (vis[u][v]) continue;
        if (v == len) {
            ans += term[u];
            term[u] = false;
            continue;
        }
        vis[u][v] = true;
        if (tmp[v] == '?') {
            for (int i = 1; i <= 4; ++i) {
                if (trie[u][i])
                    q.push(Pair(trie[u][i], v + 1));
            }
        } else if (tmp[v] == '*') {
            q.push(Pair(u, v + 1));
            for (int i = 1; i <= 4; ++i) {
                if (trie[u][i])
                    q.push(Pair(trie[u][i], v));
            }
        } else {
            if (trie[u][MAP[int(tmp[v])]])
                q.push(Pair(trie[u][MAP[int(tmp[v])]], v + 1));
        }
    }
}

int main() {
    MAP['A'] = 1, MAP['C'] = 2, MAP['T'] = 3, MAP['G'] = 4;
    scanf("%s", tmp);
    len = strlen(tmp);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s);
        insert(s);
    }
    bfs();
    printf("%d", n - ans);
    return 0;
}
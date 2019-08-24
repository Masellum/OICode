#include <algorithm>
#include <climits>
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>

const int MAXN = 100000 + 5;

int n, m, cnt, tot, ans, raw[MAXN], attach[MAXN];
int nextIdx[MAXN], next[MAXN];
bool inCache[MAXN];
std::priority_queue<std::pair<int, int>/*, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > */> q;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", raw + i);
    }
    std::copy(raw + 1, raw + n + 1, attach + 1);
    std::sort(raw + 1, raw + n + 1);
    cnt = std::unique(raw + 1, raw + n + 1) - (raw + 1);
    std::fill(next + 1, next + cnt + 1, INT_MAX);
    for (int i = 1; i <= n; ++i) {
        attach[i] = std::lower_bound(raw + 1, raw + cnt + 1, attach[i]) - raw;
    }
    cnt = std::unique(attach + 1, attach + n + 1) - (attach + 1);
    for (int i = cnt; i >= 1; --i) {
        nextIdx[i] = next[attach[i]];
        next[attach[i]] = i;
    }
    for (int i = 1; i <= cnt; ++i) {
        if (!inCache[attach[i]]) {
            ans++;
            if (tot < m) {
                inCache[attach[i]] = true;
                q.push(std::make_pair(nextIdx[i], attach[i]));
                tot++;
                continue;
            }
            while (!inCache[q.top().second]) {
                q.pop();
            }
            std::pair<int, int> p = q.top();
            inCache[p.second] = false;
            q.push(std::make_pair(nextIdx[i], attach[i]));
            inCache[attach[i]] = true;
        } else {
            q.push(std::make_pair(nextIdx[i], attach[i]));
        }
    }
    printf("%d", ans);
    return 0;
}
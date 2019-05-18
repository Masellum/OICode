#include <algorithm>
#include <cstdio>
#include <queue>

const int MAXN = 1000 + 5;

std::queue<int> q;
int n, m, arr[MAXN], size, ans;
bool inq[MAXN];

int main() {
    scanf("%d %d", &m, &n);
    int now;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &now);
        if (inq[now])
            continue;
        else {
            if (size < m) {
                q.push(now);
                inq[now] = true;
                size++;
                ans++;
            } else {
                int _ = q.front();
                q.pop();
                inq[_] = false;
                q.push(now);
                inq[now] = true;
                ans++;
            }
        }
    }
    printf("%d", ans);
    return 0;
}
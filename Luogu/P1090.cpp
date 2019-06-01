#include <cstdio>
#include <functional>
#include <queue>
#include <vector>

int n;
std::priority_queue<int, std::vector<int>, std::greater<int> > q;
int ans, t;

void init() {
    scanf("%d", &n);
    int t;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &t);
        q.push(t);
    }
}

int main(int argc, char **argv) {
    init();
    int t1, t2;
    while (/*!q.empty()*/ q.size() > 1) {
        t = 0;
        t1 = q.top();
        q.pop();
        t2 = q.top();
        q.pop();
        t = t1 + t2;
        ans += t;
        q.push(t);
    }
    printf("%d", ans);
    return 0;
}

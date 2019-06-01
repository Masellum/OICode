#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

const int MAXN = 15 + 2;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
} point[MAXN];

int n;
double dis[MAXN][MAXN];
double ans = __DBL_MAX__;
bool vis[MAXN];

auto getDis = [](const Point &a, const Point &b) -> double {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
};

void dfs(int cnt, int now, double sum) {
    if (sum > ans)
        return;
    if (cnt == n) {
        ans = std::min(ans, sum);
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            vis[i] = true;
            dfs(cnt + 1, i, sum + dis[now][i]);
            vis[i] = false;
        }
    }
}

int main() {
    scanf("%d", &n);
    double x, y;
    for (int i = 1; i <= n; ++i) {
        scanf("%lf %lf", &x, &y);
        point[i] = Point(x, y);
    }
    point[0] = Point(0.0, 0.0);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i != j) {
                dis[i][j] = getDis(point[i], point[j]);
            }
        }
    }
    dfs(0, 0, 0.0);
    printf("%.2lf", ans);
    return 0;
}
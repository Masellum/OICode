#include <algorithm>
#include <cstdio>
#include <utility>

const int MAXN = 1000 + 5;

int m, n, k, l, d;
std::pair<int, int> col[MAXN], row[MAXN], icol[MAXN], irow[MAXN];

int main() {
    scanf("%d %d %d %d %d", &m, &n, &k, &l, &d);
    for (int i = 1; i <= m; ++i) {
        row[i].first = i;
    }
    for (int i = 1; i <= n; ++i) {
        col[i].first = i;
    }
    int x, y, p, q;
    for (int i = 1; i <= d; ++i) {
        scanf("%d %d %d %d", &x, &y, &p, &q);
        if (x == p) { // 如果二者在同一行
            col[std::min(y, q)].second++;
        } else {
            row[std::min(x, p)].second++;
        }
    }
    std::sort(
        col + 1, col + n + 1,
        [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
            return a.second > b.second;
        });
    std::sort(
        row + 1, row + m + 1,
        [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
            return a.second > b.second;
        });
    std::sort(
        col + 1, col + l + 1,
        [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
            return a.first < b.first;
        });
    std::sort(
        row + 1, row + k + 1,
        [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
            return a.first < b.first;
        });
    for (int i = 1; i < k; ++i) {
        printf("%d ", row[i].first);
    }
    printf("%d\n", row[k].first);
    for (int i = 1; i < l; ++i) {
        printf("%d ", col[i].first);
    }
    printf("%d\n", col[l].first);
    return 0;
}
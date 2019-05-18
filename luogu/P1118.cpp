#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <numeric>

const int MAXN = 12 + 1;

int n, sum;
int tria[MAXN][MAXN], seq[MAXN];

int main() {
    scanf("%d %d", &n, &sum);
    for (int i = 1; i <= n; ++i) {
        tria[i][1] = tria[i][i] = 1;
    }
    for (int i = 3; i <= n; ++i) {
        for (int j = 2; j < i; ++j) {
            tria[i][j] = tria[i - 1][j - 1] + tria[i - 1][j];
        }
    }
    std::iota(seq + 1, seq + n + 1, 1);
    do {
        int s = 0;
        for (int i = 1; i <= n; ++i) {
            s += tria[n][i] * seq[i];
            if (s > sum) {
                std::sort(seq + i, seq + n + 1, std::greater<int>());
                break;
            }
        }
        if (s == sum) {
            std::for_each(seq + 1, seq + n + 1,
                          [](const int &a) { printf("%d ", a); });
            break;
        }
    } while (std::next_permutation(seq + 1, seq + n + 1));
    return 0;
}
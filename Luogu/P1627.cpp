#include <algorithm>
#include <cstdio>
#include <map>

const int MAXN = 100000 + 5;

std::map<int, int> m;

int n, b, per[MAXN], ind, ans, suml[MAXN], sumr[MAXN];

int main() {
    scanf("%d %d", &n, &b);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", per + i);
        if (per[i] < b) {
            per[i] = -1;
        } else if (per[i] > b) {
            per[i] = 1;
        } else {
            per[i] = 0;
            ind = i;
        }
    }
    for (int i = ind; i >= 1; --i) {
        suml[i] = suml[i + 1] + per[i];
        m[suml[i]]++;
    }
    for (int i = ind; i <= n; ++i) {
        if (i == ind) {
            ans += m[0];
            continue;
        }
        sumr[i] = sumr[i - 1] + per[i];
        ans += m[-sumr[i]];
    }
    printf("%d", ans);
    return 0;
}
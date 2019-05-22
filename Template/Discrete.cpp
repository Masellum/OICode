#include <algorithm>
#include <cstdio>
#include <cstring>

const int MAXN = 100000;

int arr[MAXN], raw[MAXN];

int n;

int main(int argc, char **argv) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &raw[i]);
    }
    std::copy(raw + 1, raw + n + 1, arr + 1);
    std::sort(raw + 1, raw + n + 1);
    int size = std::unique(raw + 1, raw + n + 1) - (raw + 1);
    for (int i = 1; i <= n; ++i) {
        printf("%ld ", std::lower_bound(raw + 1, raw + size + 1, arr[i]) - raw);
    }
    return 0;
}
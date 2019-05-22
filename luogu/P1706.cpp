#include <algorithm>
#include <cstdio>
#include <numeric>

const int MAXN = 9 + 1;

int arr[MAXN], n;

int main() {
    scanf("%d", &n);
    std::iota(arr + 1, arr + n + 1, 1);
    return 0;
}
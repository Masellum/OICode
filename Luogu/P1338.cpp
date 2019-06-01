#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <numeric>

const int MAXN = 50000 + 5;

std::array<int, 5> a;

int main() {
    std::iota(a.begin(), a.end(), 1);
    do {
        std::for_each(a.begin(), a.end(),
                      [](const int &a) { printf("%d ", a); });
        puts("");
    } while (std::next_permutation(a.begin(), a.end()));
    return 0;
}
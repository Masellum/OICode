#include <algorithm>
#include <cmath>
#include <cstdio>

long long x, y, ans;

int main() {
    scanf("%lld %lld", &x, &y);
    long long g = x * y, s = sqrt(g);
    for (long long i = x; i <= s; i += x) {
        if (g % i == 0 && std::__gcd(i, g / i) == x) {
            ans++;
        }
    }
    printf("%lld", ans * 2);
    return 0;
}
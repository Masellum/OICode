#include <algorithm>
#include <cstdio>

long long a, b, x, y;

void exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

int main() {
    scanf("%lld %lld", &a, &b);
    exgcd(a, b, x, y); 
    printf("%lld\n", (x % b + b) % b);
    return 0;
}
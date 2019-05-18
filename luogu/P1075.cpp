#include <cstdio>

int n;

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        if (n % i == 0) {
            printf("%d", n / i);
            break;
        }
    }
    return 0;
}
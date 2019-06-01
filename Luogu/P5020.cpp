#include <cstdio>

int T;
int n, a, b;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        if (n == 2) {
            scanf("%d %d", &a, &b);
            if (a % b == 0 || b % a == 0) {
                puts("1");
            } else {
                puts("2");
            }
        }
    }
    return 0;
}
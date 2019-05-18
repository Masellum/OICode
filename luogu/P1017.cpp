#include <algorithm>
#include <cstdio>

int n;
int r, o;
char arr[23] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
                'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};

void transform(int x, int y) {
    if (x == 0) {
        return;
    }
    if (x > 0 || x % y == 0) {
        transform(x / y, y);
        printf("%c", arr[x % y]);
    } else {
        transform(x / y + 1, y);
        printf("%c", arr[(-y + x % y)]);
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d", &r);
    printf("%d=", n);
    transform(n, r);
    printf("(base%d)", r);
    return 0;
}
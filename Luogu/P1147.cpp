#include <algorithm>
#include <cmath>
#include <cstdio>

#define isInt(x) (ceil((x)) == (x))
#define iceil(x) (int(ceil((x))))

int m;

int main() {
    scanf("%d", &m);
    for (double i = 1.5; i <= m; i += 0.5) {
        if (isInt(m / i)) {
            int len = iceil(m / i);
            if (len & 1) {
                if (!isInt(i)) {
                    continue;
                }
                if (i - len / 2 >= 1 && i + len / 2 <= m && i - len / 2 != i + len / 2) {
                    printf("%d %d\n", int(i - len / 2), int(i + len / 2));
                }
            } else {
                if (isInt(i)) {
                    continue;
                }
                if (ceil(i) - len / 2 >= 1 && floor(i) + len / 2 <= m && ceil(i) - len / 2 != floor(i) + len / 2) {
                    printf("%d %d\n", int(ceil(i) - len / 2),
                           int(floor(i) + len / 2));
                }
            }
        }
    }
    return 0;
}
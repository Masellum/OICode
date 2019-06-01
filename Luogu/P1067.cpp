#include <cstdio>

int zuigaoci;
int n;
int arr[100];

void printPower(int xishu, int cishu) {
    if (xishu == 0) {
        return;
    }
    if (cishu != n && xishu > 0) {
        printf("+");
    }
    if (cishu == 0) {
        printf("%d", xishu);
        return;
    }
    if (xishu == -1) {
        printf("-");
        xishu = -xishu;
    }
    if (cishu == 1 && xishu == 1) {
        printf("x");
        return;
    }
    if (xishu == 1) {
        printf("x^%d", cishu);
        return;
    }
    if (cishu == 1) {
        printf("%dx", xishu);
        return;
    }
    printf("%dx^%d", xishu, cishu);
}

int main() {
    scanf("%d", &n);
    zuigaoci = n;
    int xs;
    for (int i = n; i >= 0; i--) {
        scanf("%d", &xs);
        //        if (xs == 0) {
        //            zuigaoci--;
        //        }
        printPower(xs, i);
    }
    return 0;
}

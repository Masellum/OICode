#include <algorithm>
#include <cstdio>

int buc[1001] = {0};
int n, maxn = 0;

// void quickRead(int &x) {
//    char ch;
//    bool w = false;
//    ch = getchar();
//    while (ch < '0' || ch > '9') {
//        if (ch == '-') {
//            w = true;
//        }
//        ch = getchar();
//    }
//    while (ch >= '0' && ch <= '9') {
//        x = (x << 3) + (x << 1) + ch - '0';
//        ch = getchar();
//    }
//    if (w) {
//        x = -x;
//    }
//}

int main() {
    //    quickRead(n);
    scanf("%d", &n);
    int tmp;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        //        quickRead(tmp);
        scanf("%d", &tmp);
        if (buc[tmp] == 0) {
            cnt++;
            buc[tmp]++;
        }
        maxn = std::max(tmp, maxn);
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= maxn && cnt != 0; i++) {
        if (buc[i] != 0) {
            printf("%d ", i);
            cnt--;
        }
    }
    return 0;
}

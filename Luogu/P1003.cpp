#include <iostream>
#include <cstdio>

int k = -1;
int arr[10005][4];
int n, x, y;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &(arr[i][0]), &(arr[i][1]), &(arr[i][2]), &(arr[i][3]));
    }
    scanf("%d%d", &x, &y);
    for (int i = 1; i <= n; i++) {
        if (x >= arr[i][0] && x <= arr[i][0] + arr[i][2] && y >= arr[i][1] && y <= arr[i][1] + arr[i][3]) {
            k = i;
        }
    }
    printf("%d", k);
    return 0;
}

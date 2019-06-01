#include <cstdio>
#include <algorithm>

struct Farmer {
    int price;
    int amount;
} arr[5005];

int n, m, sum, cost; 

bool cmp(Farmer a, Farmer b) {
    return a.price < b.price;
}

void init() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &(arr[i].price), &(arr[i].amount));
    }
    std::sort(arr + 1, arr + m + 1, cmp);
}

int main() {
    init();
    for (int i = 1; i <= m; i++) {
        if (sum + arr[i].amount > n) {
//            sum += (n - sum);
            cost += (n - sum) * arr[i].price;
            break;
        }
        sum += arr[i].amount;
        cost += arr[i].amount * arr[i].price;
    }
    printf("%d", cost);
    return 0;
}


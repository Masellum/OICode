#include <algorithm>
#include <cstdio>

const int MAXN = 20000 + 5;

struct Person {
    int num, weight;

    bool operator<(const Person &that) {
        if (this->weight == that.weight) {
            return this->num < that.num;
        } else {
            return this->weight > that.weight;
        }
    }
} person[MAXN];

int n, k, e[11];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= 10; ++i) {
        scanf("%d", &e[i]);
    }
    for (int i = 1; i <= n; ++i) {
        person[i].num = i;
        scanf("%d", &person[i].weight);
    }
    std::sort(person + 1, person + n + 1);
    for (int i = 1; i <= n; ++i) {
        person[i].weight += e[(i - 1) % 10 + 1];
    }
    std::sort(person + 1, person + n + 1);
    for (int i = 1; i <= k; ++i) {
        printf("%d ", person[i].num);
    }
    return 0;
}
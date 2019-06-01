#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <queue>

const int MAXN = 1000000 + 5;

int n, k, arr[MAXN], que[MAXN], head, tail, pos[MAXN];

int main() {
    scanf("%d %d", &n, &k);
    // std::monotonous_queue<int> max_queue();
    // std::monotonous_queue<int/*, std::vector<int>, std::greater<int>*/ > min_queue();
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 1; i <= n; ++i) {
        while (que[tail - 1] > arr[i] && tail > head) {
            tail--;
        }
        que[tail] = arr[i];
        pos[tail++] = i;
        while (pos[head] <= i - k) {
            head++;
        }
        if (i >= k) {
            printf("%d ", que[head]);
        }
    }
    printf("\n");
    memset(que, 0, sizeof(que));
    memset(pos, 0, sizeof(pos));
    head = tail = 0;
    for (int i = 1; i <= n; ++i) {
        while (que[tail - 1] < arr[i] && tail > head) {
            tail--;
        }
        que[tail] = arr[i];
        pos[tail++] = i;
        while (pos[head] <= i - k) {
            head++;
        }
        if (i >= k) {
            printf("%d ", que[head]);
        }
    }
    return 0;
}

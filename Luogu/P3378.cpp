#include <algorithm>
#include <cstdio>

const int MAXN = 1000000 + 5;

int heap[MAXN], top;

void up(int x) {
    for (; x > 1; x >>= 1) {
        if (heap[x] < heap[x >> 1]) std::swap(heap[x], heap[x >> 1]);
        else return;
    }
}

void down(int x) {
    for (int s = x << 1; s <= top; x = s, s <<= 1) {
        s += int(s < top && heap[s] > heap[s + 1]);
        if (heap[x] > heap[s]) std::swap(heap[x], heap[s]);
        else return;
    }
}

void push(int x) {
    heap[++top] = x;
    up(top);
}

void pop() {
    heap[1] = heap[top--];
    down(1);
}

int n;

int main() {
    scanf("%d", &n);
    for (int i = 1, opt, x; i <= n; ++i) {
        scanf("%d", &opt);
        if (opt == 1) {
            scanf("%d", &x);
            push(x);
        } else if (opt == 2) printf("%d\n", heap[1]);
        else pop();
    }
    return 0;
}
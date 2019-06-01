#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

const int MAX = 50000 + 5;

int n, m, from[MAX], to[MAX], weight[MAX], head[MAX], next[MAX], cnt;

void addEdge(int f, int t, int w) {
    from[++cnt] = f;
    to[cnt] = t;
    weight[cnt] = w;
    next[cnt] = head[f];
    head[f] = cnt;
    from[++cnt] = t;
    to[cnt] = f;
    weight[cnt] = w;
    next[cnt] = head[t];
    head[t] = cnt;
}

int main() {

}
#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <utility>

const int MAXN = 100000 + 5;

int n, h[MAXN];
int nextA[MAXN], nextB[MAXN], f[MAXN][18];
// nextA[i] 表示编号为 i 的城市的东边的次近城市的编号，nextB[i] 类似。
long long fA[MAXN][18], fB[MAXN][18];

struct Node {
    Node *prev, *next;
    int pos, h;

    bool operator<(const Node &that) const { return this->h < that.h; }
} node[MAXN], *index[MAXN];
// node[i].pos 表示这个链表上的第 i 个节点对应的原城市的编号，index[i]
// 是一个指向 (表示 (编号为 i 的城市) 的链表节点) 的指针；
// 为什么用指针？因为数组模拟链表的写法会有一堆中括号套来套去实在是太丑了。

std::pair<int, int> getDistance(int x, int start) {
    int s = start;
    long long da = 0, db = 0;
    for (int j = 17; j >= 0; --j) {
        if (f[s][j] && da + db + fA[s][j] + fB[s][j] <= x) {
            da += fA[s][j], db += fB[s][j];
            s = f[s][j];
        }
    }
    if (nextA[s] != 0 && da + db + fA[s][0] <= x) {
        da += fA[s][0];
    }
    return std::make_pair(da, db);
}

int main() {
#ifndef ONLINE_JUDGE
    std::freopen("./testdata/1081/drive16.in", "r", stdin);
    std::freopen("./testdata/1081/drive.out", "w", stdout);
#endif
    std::scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        node[i].pos = i;
        std::scanf("%d", &node[i].h);
    }
    std::sort(node + 1, node + n + 1);
    for (int i = 1; i <= n; ++i) {
        index[node[i].pos] = &node[i];
    }
    for (int i = 1; i <= n; ++i) {
        node[i].prev = &node[i - 1];
        node[i].next = &node[i + 1];
    }
    node[1].prev = node[n].next = NULL;
    for (int i = 1; i <= n; ++i) {
        if (index[i]->prev == NULL) {
            if (index[i]->next != NULL) {
                nextB[i] = index[i]->next->pos;
                if (index[i]->next->next != NULL) {
                    nextA[i] = index[i]->next->next->pos;
                }
            }
        } else if (index[i]->next == NULL) {
            if (index[i]->prev != NULL) {
                nextB[i] = index[i]->prev->pos;
                if (index[i]->prev->prev != NULL) {
                    nextA[i] = index[i]->prev->prev->pos;
                }
            }
        } else {
            if (abs(index[i]->next->h - index[i]->h) >
                abs(index[i]->prev->h - index[i]->h)) {
                nextB[i] = index[i]->prev->pos;
                nextA[i] = index[i]->next->pos;
                if (index[i]->prev->prev != NULL) {
                    if (abs(index[i]->next->h - index[i]->h) >
                        abs(index[i]->prev->prev->h - index[i]->h)) {
                        nextA[i] = index[i]->prev->prev->pos;
                    } else if (abs(index[i]->next->h - index[i]->h) ==
                        abs(index[i]->prev->prev->h - index[i]->h)) {
                            if (index[i]->next->h > index[i]->prev->prev->h) {
                                nextA[i] = index[i]->prev->prev->pos;
                            }
                    }
                }
            } else if (abs(index[i]->next->h - index[i]->h) <
                       abs(index[i]->prev->h - index[i]->h)) {
                nextB[i] = index[i]->next->pos;
                nextA[i] = index[i]->prev->pos;
                if (index[i]->next->next != NULL) {
                    if (abs(index[i]->prev->h - index[i]->h) >
                        abs(index[i]->next->next->h - index[i]->h)) {
                        nextA[i] = index[i]->next->next->pos;
                    } else if (abs(index[i]->prev->h - index[i]->h) == 
                        abs(index[i]->next->next->h - index[i]->h)) {
                            if (index[i]->prev->h > index[i]->next->next->h) {
                                nextA[i] = index[i]->next->next->pos;
                            }
                        }
                }
            } else {
                if (index[i]->next->h > index[i]->prev->h) {
                    nextB[i] = index[i]->prev->pos;
                    nextA[i] = index[i]->next->pos;
                } else {
                    nextA[i] = index[i]->prev->pos;
                    nextB[i] = index[i]->next->pos;
                }
            }
        }
        if (index[i]->prev != NULL) {
            index[i]->prev->next = index[i]->next;
        }
        if (index[i]->next != NULL) {
            index[i]->next->prev = index[i]->prev;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (nextA[i] != 0) {
            fA[i][0] = abs(index[nextA[i]]->h - index[i]->h);
            if (nextB[nextA[i]] != 0) {
                fB[i][0] = abs(index[nextB[nextA[i]]]->h - index[nextA[i]]->h);
            }
        }
        f[i][0] = nextB[nextA[i]];
    }
    for (int j = 1; j <= 17; ++j) {
        for (int i = 1; i <= n; ++i) {
            f[i][j] = f[f[i][j - 1]][j - 1];
            fA[i][j] = fA[i][j - 1] + fA[f[i][j - 1]][j - 1];
            fB[i][j] = fB[i][j - 1] + fB[f[i][j - 1]][j - 1];
        }
    }
    int x, s, m;
    std::scanf("%d", &x);
    double min = __DBL_MAX__;
    for (int i = 1; i <= n; ++i) {
        std::pair<int, int> p = getDistance(x, i);
        if (p.second != 0 && 1.0 * p.first / p.second < min) {
            min = 1.0 * p.first / p.second;
            s = i;
        }
    }
    std::printf("%d\n", s);
    std::scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        std::scanf("%d %d", &s, &x);
        std::pair<int, int> p = getDistance(x, s);
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}
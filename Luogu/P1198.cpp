#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>

#ifndef ONLINE_JUDGE
#define DEBUG(x) std::cerr << #x << "=" << x << std::endl
#endif

const int MAXM = 200000 + 5;

int m, d, len, t;

int ST[MAXM][20];

int main() {
    scanf("%d%d", &m, &d);
    for (int i = 1; i <= m; ++i) {
        char op;
        int l;
        scanf("\n%c%d", &op, &l);
        // #ifndef ONLINE_JUDGE
        //         DEBUG(op);
        //         DEBUG(l);
        // #endif
        if (op == 'Q') {
            // DEBUG(l);
            // DEBUG(log2(l));
            // DEBUG(len);
            // DEBUG(len - l + 1);
            // DEBUG(1 << int(log2(l)));
            // DEBUG(len - (1 << int(log2(l))));
            t = std::max(ST[len - l + 1][int(log2(l))],
                         ST[len - (1 << int(log2(l))) + 1][int(log2(l))]);
            printf("%d\n", t);
        } else if (op == 'A') {
            len++;
            l = ((l % d) + (t % d)) % d;
            ST[len][0] = l;
            for (int j = 1; j <= 18 && len - (1 << j) + 1 >= 1; ++j) {
                int formerMax = std::max(ST[len - (1 << j) + 1][j - 1],
                                         ST[len - (1 << (j - 1)) + 1][j - 1]);
                ST[len - (1 << j) + 1][j] = std::max(formerMax, l);
            }
        }
    }
    return 0;
}
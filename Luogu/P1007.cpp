#include <cstdio>
#include <algorithm>
#include <cmath>
#include <climits>

const int MAXN = 5005;

int l, n, pos[MAXN], middest;
int mid;

int main(int argc, char const *argv[])
{
    scanf("%d%d", &l, &n);
    middest = l + 1;
    if (l == 0 || n == 0)
    {
        printf("0 0");
        return 0;
    }
    mid = l / 2 + 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &pos[i]);
    }
    std::sort(pos + 1, pos + n + 1);
    for (int i = 1; i <= n; ++i)
    {
        if (pos[i - 1] < mid && pos[i] >= mid) {
            middest = i;
        }
    }
    if (pos[middest - 1] > l - pos[middest] + 1) {
        --middest;
    }
    // if (l & 1)
    // {
    //     for (int i = 1; i <= n; ++i)
    //     {
    //         if (std::abs(pos[i] - mid) < std::abs(middest - mid))
    //         {
    //             middest = pos[i];
    //         }
    //     }
    // }
    // else
    // {
    //     for (int i = 1; i <= n; ++i)
    //     {
    //         if (pos[i] < mid)
    //         {
    //             if (mid - pos[i] - 1 < mid - middest - 1)
    //             {
    //                 middest = pos[i];
    //             }
    //         }
    //         else
    //         {
    //             if (pos[i] - mid < middest - mid)
    //             {
    //                 middest = pos[i];
    //             }
    //         }
    //     }
    // }
    printf("%d %d", std::min(pos[middest], l - pos[middest] + 1), std::max(pos[n], l - pos[1] + 1));
    return 0;
}
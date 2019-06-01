// #include <algorithm>
// #include <climits>
// #include <cstdio>
// #include <queue>
// #include <utility>

// #define lb(x) ((x) & (-(x)))

// const int MAXN = 100000 + 5, SIZE = 50000 + 5;

// template <typename Compare = std::less<int>> struct FenwickTree {
//     int *tree = new int[SIZE];
//     Compare cmp;

//     void modify(int index, int x) {
//         for (; index <= SIZE; index += lb(index)) {
//             tree[index] = std::min({tree[index], x}, cmp);
//         }
//     }

//     int query(int range) {
//         int res = std::max({INT_MIN, INT_MAX}, cmp);
//         for (; range; range -= lb(range)) {
//             res = std::min({tree[range], res}, cmp);
//         }
//         return res;
//     }
// };

// int n, arr[MAXN], longestDecreasingSubsequense[MAXN],
//     longestIncreasingSubsequense[MAXN];

// int main() {
//     int now, range = INT_MIN;
//     while (scanf("%d", &now) != EOF) {
//         arr[++n] = now;
//         range = std::max(range, now);
//     }
//     FenwickTree<std::less<int>> tree1;
//     FenwickTree<std::greater<int>> tree2;

//     longestDecreasingSubsequense[1] = 1;
//     longestIncreasingSubsequense[1] = 1;

//     tree1.modify(1, 1);
//     tree2.modify(1, 1);
//     for (int i = 2; i <= n; ++i) {
//         longestDecreasingSubsequense[i] = tree1.query(arr[i] - 1) + 1;
//         longestIncreasingSubsequense[i] = tree2.query(arr[i] - 1) + 1;
//     }
// }
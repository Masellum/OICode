#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

const int MAX = 100000 + 200 + 5;

int n, m, q, len;
std::string book[MAX];
std::vector<int> v;

int main() {
    std::cin >> n;
    std::string str;
    for (int i = 1; i <= n; ++i) {
        std::cin >> str;
        book[++len] = str;
        v.push_back(len);
    }
    std::cin >> m;
    for (int i = 1, x; i <= m; ++i) {
        std::cin >> str >> x;
        book[++len] = str;
        v.insert(v.begin() + x, len);
    }
    std::cin >> q;
    for (int i = 1, x; i <= q; ++i) {
        std::cin >> x;
        std::cout << book[v[x]] << std::endl;
    }
    return 0;
}
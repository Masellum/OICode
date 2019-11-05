#include <map>
#include <cstring>
#include <iostream>

const int MAXN = 100010

std::string name;
int n, t[MAXN];
std::map<std::string, int> mp;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> name;
        mp[name] = i;
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> name;
        int a = n - mp[name] + 1;
        for (int p = a - 1; p; p -= p & -p) ans += t[p];
        for (int p = a; p <= n; p += p & -p) ++t[p];
    }
    std::cout << ans;
    return 0;
}
#include <iostream>
#include <utility>
#include <cstdio>
//#include <string>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int n, m;
std::pair<int, std::string> arr[100005];
int head = 1;

void init() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> arr[i].first >> arr[i].second;
    }
}

void turn(int step, bool direction, bool face) {
    //direction为0是向左，为1是向右 
    //face为0向里，face为1向外 
    //所以face&&direction为true时为顺时针，face||direction为false时为顺时针，其余为逆时针 
    if ((face && direction) || !(face || direction)) {
//        if (head - step <= 0) {
//            head = n + head - step;
////            DEBUG(head);
//            return;
//        }
        while (head - step <= 0) {
            head = n + head - step;
//            DEBUG(head);
            return;
        }
        head -= step;
//        DEBUG(head);
        return;
    }
//    if (head + step > n) {
//        head = head + step - n;
////        DEBUG(head);
//        return;
//    }
    while (head + step > n) {
        head = head + step - n;
//        DEBUG(head);
        return;
    }
    head += step;
//    DEBUG(head);
    return;
}

int main() {
//    freopen("testdata.in", "r", stdin);
//    std::ios::sync_with_stdio(false);
    init();
    int d, c;
    for (int i = 1; i <= m; ++i) {
        std::cin >> d >> c;
        turn(c, d, arr[head].first);
    }
    std::cout << arr[head].second;
    return 0;
}

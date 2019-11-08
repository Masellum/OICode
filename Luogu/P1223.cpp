#include <algorithm>
#include <cstdio>

typedef long long ll;

const int MAXN = 1005;

int n;
ll sum;
struct Student {
    int id, t;
    ll w;
    
    friend bool operator<(const Student &lhs, const Student &rhs) {
        return lhs.t < rhs.t;
    }
} s[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i].t);
        s[i].id = i;
    }
    std::sort(s + 1, s + n + 1);
    s[1].w = 0;
    for (int i = 2; i <= n; i++) {
        s[i].w = 1ll * s[i - 1].t + s[i - 1].w;
        sum += s[i].w;
    }
    double avg = double(sum) / n;
    for (int i = 1; i <= n; i++) printf("%d ", s[i].id);
    printf("\n%.2lf", avg);
    return 0;
}

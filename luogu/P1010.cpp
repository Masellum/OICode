#include <algorithm>
#include <cstdio>
#include <stack>

int n;

void solve(int x) {
    if (x == 0) {
        printf("0");
        return;
    }
    if (x == 1) {
        printf("2(0)");
        return;
    }
    if (x == 2) {
        printf("2");
        return;
    }
    std::stack<int> st;
    int cnt = 0;
    while (x) {
        if (x & 1) {
            st.push(cnt);
        }
        cnt++;
        x >>= 1;
    }
    int t = 0;
    while (st.size() > 1) {
        t = st.top();
        st.pop();
        if (t != 1) {
            printf("2(");
            solve(t);
            printf(")+");
        } else {
            printf("2+");
        }
    }
    t = st.top();
    st.pop();
    if (t != 1) {
        printf("2(");
        solve(t);
        printf(")");
    } else {
        printf("2");
    }
}

int main() {
    scanf("%d", &n);
    solve(n);
    return 0;
}
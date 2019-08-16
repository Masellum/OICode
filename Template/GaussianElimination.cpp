#include <algorithm>
#include <cmath>
#include <cstdio>

const int MAXN = 100 + 5;

int n;
double a[MAXN][MAXN];

bool gauss_jordan(double mat[MAXN][MAXN]) {
    for (int i = 1; i <= n; ++i) {
        int idx = i;
        for (int j = i + 1; j <= n; ++j) {
            if (fabs(mat[j][i]) > fabs(mat[idx][i])) idx = j;
        }
        if (fabs(mat[idx][i]) <= 1e-10) return false;
        if (i != idx) {
            for (int j = i; j <= n + 1; ++j) {
                std::swap(mat[i][j], mat[idx][j]);
            }
        }
        for (int j = 1; j <= n; ++j) {
            if (j != i) {
                for (int k = n + 1; k >= i; --k) {
                    mat[j][k] -= mat[i][k] / mat[i][i] * mat[j][i];
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n + 1; ++j) {
            scanf("%lf", &a[i][j]);
        }
    }
    if (gauss_jordan(a)) {
        for (int i = 1; i <= n; ++i) {
            printf("%.2f\n", a[i][n + 1] / a[i][i]);
        }
    } else {
        puts("No Solution");
    }
    return 0;
}
#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 100 + 3, MOD = int(1e9 + 7);

int n;
ll k;

struct Matrix {
    int mat[MAXN][MAXN];

    Matrix operator*(const Matrix &that) {
        Matrix ret;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                ret.mat[i][j] = 0;
                for (int k = 1; k <= n; ++k) {
                    ret.mat[i][j] = (ret.mat[i][j] % MOD + 1LL * this->mat[i][k] * that.mat[k][j] % MOD) % MOD;
                }
            }
        }
        return ret;
    }
} A;

Matrix matrixFastPower(Matrix a, ll k) {
    Matrix base = a, res;
    for (int i = 1; i <= n; ++i) {
        res.mat[i][i] = 1;
    }
    for (; k; k >>= 1, base = base * base) {
        if (k & 1) {
            res = res * base;
        }
    }
    return res;
}

int main() {
    scanf("%d %lld", &n, &k);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &A.mat[i][j]);
        }
    }
    A = matrixFastPower(A, k);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%d ", A.mat[i][j] % MOD);
        }
        puts("");
    }
    return 0;
}
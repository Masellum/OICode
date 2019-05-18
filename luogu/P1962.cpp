#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MOD = int(1e9 + 7);

ll n;

struct Matrix {
    int col, row;
    ll *data;

    Matrix() : col(0), row(0), data(nullptr) {}

    Matrix(int col, int row) : col(col), row(row) {
        data = new ll[(col + 1) * (row + 1)];
        memset(data, 0, sizeof(ll) * (col + 1) * (row + 1));
    }

    Matrix &operator=(const Matrix &that) {
        this->col = that.col;
        this->row = that.row;
        if (this != &that) {
            delete[] data;
            this->data = new ll[sizeof(ll) * (that.col + 1) * (that.row + 1)];
            memcpy(data, that.data,
                   sizeof(ll) * (that.col + 1) * (that.row + 1));
        }
        return *this;
    }

    ~Matrix() {
        col = 0;
        row = 0;
        if (data != nullptr) {
            delete[] data;
        }
    }

    ll &at(int x, int y) { return data[x * col + y]; }

    Matrix operator*(Matrix &that) {
        Matrix res(this->row, that.col);
        for (int i = 1; i <= this->row; ++i) {
            for (int j = 1; j <= that.col; ++j) {
                ll sum = 0;
                for (int k = 1; k <= this->col; ++k) {
                    sum += this->at(i, k) % MOD * that.at(k, j) % MOD;
                    sum %= MOD;
                }
                res.at(i, j) += sum % MOD;
                res.at(i, j) %= MOD;
            }
        }
        return res;
    }
} F(1, 2), C(2, 2);

Matrix matrixFastPower(Matrix x, ll k) {
    Matrix res = x;
    for (k--; k; x = x * x, k >>= 1) {
        if (k & 1) {
            res = res * x;
        }
    }
    return res;
}

int main() {
    scanf("%lld", &n);
    if (n == 1) {
        puts("1");
        return 0;
    }
    if (n == 2) {
        puts("1");
        return 0;
    }
    F.at(1, 1) = 1;
    F.at(1, 2) = 1;
    C.at(1, 1) = 0;
    C.at(1, 2) = C.at(2, 1) = C.at(2, 2) = 1;
    C = matrixFastPower(C, n);
    F = F * C;
    printf("%lld", F.at(1, 2));
    return 0;
}
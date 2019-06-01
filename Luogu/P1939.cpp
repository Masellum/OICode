#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using int_t = unsigned long long int;

const int_t MOD = int(1e9 + 7);

template <typename ValType> class Matrix;

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &mat);

template <typename T>
std::istream &operator>>(std::istream &is, const Matrix<T> &mat);

template <typename ValType> class Matrix {
  private:
    int_t row;
    int_t col;
    int_t num;
    int_t size;
    ValType *data;

  public:
    ~Matrix() {
        if (data != nullptr) {
            delete[] data;
        }
    }

    Matrix(const Matrix<ValType> &that)
        : row(that.row), col(that.col), num(that.num), size(that.size) {
        data = new ValType[that.num];
        memcpy(data, that.data, that.size);
    }

    Matrix(int_t r, int_t c) : row(r), col(c) {
        this->row = r;
        this->col = c;
        num = (row + 1) * (col + 1);
        data = new ValType[num];
        size = sizeof(ValType) * num;
        memset(data, 0, size);
    }

    Matrix<ValType> &operator=(const Matrix<ValType> &that) {
        this->row = that.row;
        this->col = that.col;
        this->num = that.num;
        if (this != &that) {
            delete[] data;
            this->size = that.size;
            this->data = new ValType[num];
            memcpy(data, that.data, size);
        }
        return *this;
    }

    Matrix(Matrix &&that) : row(0), col(0), num(0), size(0), data(nullptr) {
        col = that.col;
        row = that.row;
        num = that.num;
        size = that.size;
        data = that.data;
        that.row = that.col = that.num = that.size = 0;
        that.data = nullptr;
    }

    Matrix<ValType> &operator=(Matrix &&that) {
        if (this != &that) {
            delete[] data;
            this->row = that.row;
            this->col = that.col;
            this->num = that.num;
            this->size = that.size;
            data = that.data;
            that.data = nullptr;
            that.row = that.col = that.num = that.size = 0;
        }
        return *this;
    }

    ValType &at(int r, int c) { return data[r * col + c]; }

    Matrix<ValType> operator*(Matrix<ValType> &that) {
        Matrix<ValType> result(this->row, that.col);

        for (int_t i = 1; i <= this->row; ++i) {
            for (int_t j = 1; j <= that.col; ++j) {
                int_t sum = 0;
                for (int_t k = 1; k <= this->col; ++k) {
                    sum = (sum % MOD +
                           this->at(i, k) % MOD * that.at(k, j) % MOD) %
                          MOD;
                }
                result.at(i, j) += sum % MOD;
                result.at(i, j) %= MOD;
            }
        }
        return result;
    }

    int_t getRow() { return row; }

    int_t getCol() { return col; }
};

template <typename ValType>
std::ostream &operator<<(std::ostream &os, Matrix<ValType> &mat) {
    for (int_t i = 1; i <= mat.getRow(); ++i) {
        for (int_t j = 1; j <= mat.getCol(); ++j) {
            os << mat.at(i, j) % MOD << " ";
        }
        os << std::endl;
    }
    return os;
}

template <typename ValType>
std::istream &operator>>(std::istream &is, Matrix<ValType> &mat) {
    for (int_t i = 1; i <= mat.getRow(); ++i) {
        for (int_t j = 1; j <= mat.getCol(); ++j) {
            is >> mat.at(i, j);
            mat.at(i, j) %= MOD;
        }
    }
    return is;
}

using Matrix_t = Matrix<int_t>;

Matrix_t fastPower(Matrix_t mat, int k) {
    Matrix_t result = mat;
    for (k--; k; k >>= 1, mat = mat * mat) {
        if (k & 1) {
            result = result * mat;
        }
    }
    return result;
}

Matrix_t initial(1, 3), multyplier(3, 3), result(1, 3);

int_t T, n;

int main() {
    initial.at(1, 1) = initial.at(1, 2) = initial.at(1, 3) = 1;
    multyplier.at(1, 3) = multyplier.at(2, 1) = multyplier.at(3, 2) =
        multyplier.at(3, 3) = 1;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        if (n <= 3) {
            std::cout << 1 << std::endl;
            continue;
        } else {
            result = fastPower(multyplier, n - 3);
            result = initial * result;
            std::cout << result.at(1, 3) << std::endl;
        }
    }
    return 0;
}
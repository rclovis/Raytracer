template <int rows, int cols>
class Matrix {
    public:
        Matrix();
        Matrix(const Matrix &other);
        ~Matrix() = default;

        Matrix operator+(const Matrix &other) const;
        void operator+=(const Matrix &other);

        Matrix operator-(const Matrix &other) const;
        void operator-=(const Matrix &other);

        Matrix operator*(const Matrix &other) const;
        void operator*=(const Matrix &other);
        Matrix operator*(double scalar) const;
        void operator*=(double scalar);

        Matrix operator/(double scalar) const;
        void operator/=(double scalar);

        double data[rows][cols];
};

template <int rows, int cols>
Matrix<rows, cols>::Matrix()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            this->matrix[i][j] = 0;
}

template <int rows, int cols>
Matrix<rows, cols>::Matrix(const Matrix<rows, cols> &other)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            this->matrix[i][j] = other.matrix[i][j];
}

template <int rows, int cols>
Matrix<rows, cols> Matrix<rows, cols>::operator+(const Matrix<rows, cols> &other) const
{
    Matrix<rows, cols> result;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
    return result;
}

template <int rows, int cols>
void Matrix<rows, cols>::operator+=(const Matrix<rows, cols> &other)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            this->matrix[i][j] += other.matrix[i][j];
}

template <int rows, int cols>
Matrix<rows, cols> Matrix<rows, cols>::operator-(const Matrix<rows, cols> &other) const
{
    Matrix<rows, cols> result;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
    return result;
}

template <int rows, int cols>
void Matrix<rows, cols>::operator-=(const Matrix<rows, cols> &other)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            this->matrix[i][j] -= other.matrix[i][j];
}

template <int rows, int cols>
Matrix<rows, cols> Matrix<rows, cols>::operator*(const Matrix<rows, cols> &other) const
{
    Matrix<rows, cols> result;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int k = 0; k < rows; k++)
                result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
    return result;
}

template <int rows, int cols>
void Matrix<rows, cols>::operator*=(const Matrix<rows, cols> &other)
{
    Matrix<rows, cols> result;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int k = 0; k < rows; k++)
                result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
    *this = result;
}

template <int rows, int cols>
Matrix<rows, cols> Matrix<rows, cols>::operator*(double other) const
{
    Matrix<rows, cols> result;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.matrix[i][j] = this->matrix[i][j] * other;
    return result;
}

template <int rows, int cols>
void Matrix<rows, cols>::operator*=(double other)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            this->matrix[i][j] *= other;
}

template <int rows, int cols>
Matrix<rows, cols> Matrix<rows, cols>::operator/(double other) const
{
    Matrix<rows, cols> result;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.matrix[i][j] = this->matrix[i][j] / other;
    return result;
}

template <int rows, int cols>
void Matrix<rows, cols>::operator/=(double other)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            this->matrix[i][j] /= other;
}
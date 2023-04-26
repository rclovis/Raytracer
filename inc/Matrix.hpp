/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Matrix
*/

#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <math.h>

namespace mat {
    template<typename T, int rows, int cols>
    class Matrix {
        public:
            // Constructeur par défaut
            Matrix() {
                matrix_.resize(rows, std::vector<T>(cols));
            }

            Matrix (const std::initializer_list<std::initializer_list<T>>& list) {
                matrix_.resize(rows, std::vector<T>(cols));
                if (list.size() != rows || list.begin()->size() != cols) {
                    throw std::invalid_argument("Invalid initializer list size for assignment");
                }
                size_t row = 0;
                for (const auto& sublist : list) {
                    size_t col = 0;
                    for (const auto& value : sublist) {
                        matrix_[row][col] = value;
                        ++col;
                    }
                    ++row;
                }
            }

            // Constructeur avec initialisation
            Matrix(const std::vector<std::vector<T>>& matrix) {
                if (matrix.size() != rows || matrix[0].size() != cols) {
                    throw std::runtime_error("La taille de la matrice ne correspond pas à la taille spécifiée.");
                }
                matrix_ = matrix;
            }

            // Opérateur d'addition
            Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols>& other) const {
                Matrix<T, rows, cols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
                    }
                }
                return result;
            }

            //equality operator
            bool operator==(const Matrix<T, rows, cols>& other) const {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (matrix_[i][j] != other.matrix_[i][j]) {
                            return false;
                        }
                    }
                }
                return true;
            }

            // Opération d'addition et affectation
            void operator+=(const Matrix<T, rows, cols>& other) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrix_[i][j] += other.matrix_[i][j];
                    }
                }
            }

            // Opérateur de soustraction
            Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols>& other) const {
                Matrix<T, rows, cols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
                    }
                }
                return result;
            }

            // Opération de soustraction et affectation
            void operator-=(const Matrix<T, rows, cols>& other) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrix_[i][j] -= other.matrix_[i][j];
                    }
                }
            }

            // Opérateur de multiplication
            template<int otherCols>
            Matrix<T, rows, otherCols> operator*(const Matrix<T, cols, otherCols>& other) const {
                Matrix<T, rows, otherCols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < otherCols; ++j) {
                        for (int k = 0; k < cols; ++k) {
                            result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
                        }
                    }
                }
                return result;
            }

            // Opérateur de multiplication et affectation
            template<int otherCols>
            void operator*=(const Matrix<T, cols, otherCols>& other) {
                Matrix<T, rows, otherCols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < otherCols; ++j) {
                        for (int k = 0; k < cols; ++k) {
                            result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
                        }
                    }
                }
                matrix_ = result.matrix_;
            }

            // Opérateur de multiplication par un scalaire
            Matrix<T, rows, cols> operator*(const T& scalar) const {
                Matrix<T, rows, cols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result.matrix_[i][j] = matrix_[i][j] * scalar;
                    }
                }
                return result;
            }

            // Opérateur de multiplication par un scalaire et affectation
            void operator*=(const T& scalar) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrix_[i][j] *= scalar;
                    }
                }
            }

            // Opérateur de division
            Matrix<T, rows, cols> operator/(const T& scalar) const {
                Matrix<T, rows, cols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result.matrix_[i][j] = matrix_[i][j] / scalar;
                    }
                }
                return result;
            }

            // Opérateur de division et affectation
            void operator/=(const T& scalar) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrix_[i][j] /= scalar;
                    }
                }
            }

            // Méthode pour accéder aux éléments de la matrice

            T& operator()(int row, int col) {
                return matrix_[row][col];
            }

            const T& operator()(int row, int col) const {
                return matrix_[row][col];
            }

            // Méthode pour afficher la matrice
            void print() const {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        std::cout << matrix_[i][j] << " ";
                    }
                    std::cout << std::endl;
                }
            }

            // Méthode pour afficher la matrice avec std::cout
            friend std::ostream& operator<<(std::ostream& os, const Matrix<T, rows, cols>& matrix) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        os << matrix.matrix_[i][j] << " ";
                    }
                    if (i != rows - 1)
                        os << std::endl;
                }
                return os;
            }

            // Méthode pour définir le contenu de la matrice
            void set(const std::vector<std::vector<T>>& matrix) {
                if (matrix.size() != rows || matrix[0].size() != cols) {
                    throw std::runtime_error("La taille de la matrice ne correspond pas à la taille spécifiée.");
                }
                matrix_ = matrix;
            }

            std::vector<std::vector<T>> matrix_;
    };


    static Matrix<float, 3, 3> rotationMatrixX (float angle) {
        float radAngle = -angle * M_PI / 180;
        Matrix<float, 3, 3> result = {
            {1, 0, 0},
            {0, cos(radAngle), -sin(radAngle)},
            {0, sin(radAngle), cos(radAngle)}
        };
        return result;
    }

    static Matrix<float, 3, 3> rotationMatrixY (float angle) {
        float radAngle = -angle * M_PI / 180;
        Matrix<float, 3, 3> result = {
            {cos(radAngle), 0, sin(radAngle)},
            {0, 1, 0},
            {-sin(radAngle), 0, cos(radAngle)}
        };
        return result;
    }

    static Matrix<float, 3, 3> rotationMatrixZ (float angle) {
        float radAngle = -angle * M_PI / 180;
        Matrix<float, 3, 3> result = {
            {cos(radAngle), -sin(radAngle), 0},
            {sin(radAngle), cos(radAngle), 0},
            {0, 0, 1}
        };
        return result;
    }

    static Matrix<float, 3, 3> rotationMatrix (float angleX, float angleY, float angleZ) {
        return rotationMatrixX(angleX) * rotationMatrixY(angleY) * rotationMatrixZ(angleZ);
    }

    static Matrix<float, 4, 4> translationMatrix (float x, float y, float z) {
        Matrix<float, 4, 4> result = {
            {1, 0, 0, x},
            {0, 1, 0, y},
            {0, 0, 1, z},
            {0, 0, 0, 1}
        };
        return result;
    }

    static Matrix<float, 4, 4> scaleMatrix (float x, float y, float z) {
        Matrix<float, 4, 4> result = {
            {x, 0, 0, 0},
            {0, y, 0, 0},
            {0, 0, z, 0},
            {0, 0, 0, 1}
        };
        return result;
    }

    template<typename T, int rows, int cols>
    static Matrix<T, rows, cols> identityMatrix() {
        Matrix<T, rows, cols> result;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i == j) {
                    result.matrix_[i][j] = 1;
                }
                else {
                    result.matrix_[i][j] = 0;
                }
            }
        }
        return result;
    }

    template<typename T, int rows, int cols>
    static Matrix<T, rows, cols> normalizeMatrix(const Matrix<T, rows, cols>& matrix) {
        Matrix<T, rows, cols> result;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.matrix_[i][j] = matrix.matrix_[i][j] / matrix.matrix_[rows - 1][cols - 1];
            }
        }
        return result;
    }

    template<typename T, int rows, int cols>
    static Matrix<T, rows, cols> capMatrix(const Matrix<T, rows, cols>& matrix, T maxValue) {
        T max = 0;
        Matrix<T, rows, cols> result;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                max = std::max(max, matrix.matrix_[i][j]);
            }
        }
        if (max > maxValue) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.matrix_[i][j] = matrix.matrix_[i][j] - (max - maxValue);
                    if (result.matrix_[i][j] < 0)
                        result.matrix_[i][j] = 0;
                }
            }
        }
        else {
            result = matrix;
        }
        return result;
    }
}
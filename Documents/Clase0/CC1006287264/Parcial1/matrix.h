#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Matriz {
private:
    int rows, cols;
    T *data;

public:
    Matriz(int rows, int cols) : rows(rows), cols(cols) {
    this->rows= rows;
    this->cols= cols;
    data = new T[rows * cols];
    }

    ~Matriz() {
        delete[] data;
    }

    int getFilas() const {
        return rows;
    }

    int getColumnas() const {
        return cols;
    }
    T* operator[](int fila) {
    return &data[fila * cols] ;
    }

    T &at(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Posición de la matriz fuera de rango");
        }
        return data[row * cols + col];
    }

    T at(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Posición de la matriz fuera de rango");
        }
        return data[row * cols + col];
    }
    
    
    void asignar(initializer_list<initializer_list<T>> valores) {
    if (valores.size() != rows) {
        throw invalid_argument("Número incorrecto de filas");
    }
    int i = 0;
    for (auto fila : valores) {
        if (fila.size() != cols) {
            throw invalid_argument("Número incorrecto de columnas en la fila " + to_string(i));
        }
        int j = 0;
        for (auto valor : fila) {
            at(i, j) = valor;
            j++;
        }
        i++;
    }
}
    




    void operator=(const Matriz<T> &rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw invalid_argument("Las matrices tienen diferentes dimensiones");
        }
        for (int i = 0; i < rows * cols; i++) {
            data[i] = rhs.data[i];
        }
    }

    Matriz<T> operator+(const Matriz<T> &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw invalid_argument("Las matrices tienen diferentes dimensiones");
        }
        Matriz<T> result(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] + rhs.data[i];
        }
        return result;
    }

    Matriz<T> operator-(const Matriz<T> &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw invalid_argument("Las matrices tienen diferentes dimensiones");
        }
        Matriz<T> result(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] - rhs.data[i];
        }
        return result;
    }

    void operator+=(const Matriz<T> &rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw invalid_argument("Las matrices tienen diferentes dimensiones");
        }
        for (int i = 0; i < rows * cols; i++) {
            data[i] += rhs.data[i];
        }
    }

    void operator-=(const Matriz<T> &rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw invalid_argument("Las matrices tienen diferentes dimensiones");
        }
        for (int i = 0; i < rows * cols; i++) {
            data[i] -= rhs.data[i];
        }
    }

    Matriz<T> transpuesta() const {
        Matriz<T> result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.at(j, i) = at(i, j);
            }
        }
        return result;
    }
};


#endif

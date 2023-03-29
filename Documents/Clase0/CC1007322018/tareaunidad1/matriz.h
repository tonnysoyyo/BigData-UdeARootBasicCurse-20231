#include <cmath>
#include <iostream>

template<typename T> // Declaración de una clase plantilla llamada Matriz que toma un parámetro de tipo T.
class Matriz {
public:
    Matriz(size_t rows, size_t cols) : rows_(rows), cols_(cols) { // Constructor que toma el número de filas y columnas de la matriz como argumentos.
        data_ = new T[rows * cols]; // Se asigna memoria dinámicamente para el arreglo de elementos de la matriz.
    }

    ~Matriz() { // Destructor que se encarga de liberar la memoria asignada dinámicamente para el arreglo de elementos de la matriz.
        delete[] data_;
    }

    T& operator()(size_t i, size_t j) { // Sobrecarga del operador () que se encarga de devolver una referencia al elemento (i, j) de la matriz.
        return data_[i * cols_ + j];
    }

    const T& operator()(size_t i, size_t j) const { // Sobrecarga del operador () para una matriz constante.
        return data_[i * cols_ + j];
    }

    void imprimir() const { // Método que imprime la matriz.
        for (size_t i = 0; i < rows_; i++) { // Se recorre cada fila de la matriz.
            for (size_t j = 0; j < cols_; j++) { // Se recorre cada columna de la matriz.
                std::cout << (*this)(i, j) << " "; // Se imprime el elemento (i, j) de la matriz.
            }
            std::cout << std::endl; // Se agrega un salto de línea al final de cada fila.
        }
    }

    Matriz<T> transpuesta() const { // Método que devuelve la transpuesta de la matriz.
        Matriz<T> tr(cols_, rows_); // Se crea una nueva matriz con las filas y columnas intercambiadas.
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                tr(j, i) = (*this)(i, j); // Se copia el elemento (i, j) de la matriz original en la posición (j, i) de la matriz transpuesta.
            }
        }
        return tr; // Se devuelve la matriz transpuesta.
    }

    Matriz& operator=(const Matriz& other) { // Sobrecarga del operador =
        if (this == &other) { // Verifica si las matrices son la misma
            return *this; // Si son la misma matriz, se retorna la referencia a sí misma
        }

    // Si las matrices no son la misma, se libera la memoria asignada dinámicamente a la matriz actual
        delete[] data_;

    // Se copian las filas y columnas de la matriz other
        rows_ = other.rows_;
        cols_ = other.cols_;

    // Se asigna memoria dinámicamente para el arreglo de elementos de la matriz
        data_ = new T[rows_ * cols_];

    // Se copian los elementos de la matriz other en la matriz actual
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
             (*this)(i, j) = other(i, j);
        }
    }

     return *this; // Se retorna la referencia a la matriz actualizada
}

    Matriz operator+(const Matriz& other) const { // Sobrecarga del operador +
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Las matrices deben tener el mismo tamaño para sumarse");
        }

        Matriz result(rows_, cols_); // Crea una nueva matriz del mismo tamaño
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                result(i, j) = (*this)(i, j) + other(i, j); // Suma los elementos de las matrices
            }
        }
        return result;
    }

    Matriz operator-(const Matriz& other) const {// Sobrecarga del operador -
        if (rows_ != other.rows_ || cols_ != other.cols_) {// Verifica que las dos matrices tengan el mismo tamaño
            throw std::invalid_argument("Las matrices deben tener el mismo tamaño para restarse");
        }

        Matriz result(rows_, cols_); // Crea una nueva matriz del mismo tamaño
        for (int i = 0; i < rows_; i++) { 
            for (int j = 0; j < cols_; j++) {
                result(i, j) = (*this)(i, j) - other(i, j); // Resta los elementos de las matrices
            }
        }
        return result;
    }

    Matriz& operator+=(const Matriz& other) { // Sobrecarga del operador +=
        if (rows_ != other.rows_ || cols_ != other.cols_) {// Verifica que las dos matrices tengan el mismo tamaño
            throw std::invalid_argument("Las matrices deben tener el mismo tamaño para sumarse");
        }

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                (*this)(i, j) += other(i, j);
            }
        }
        return *this; // Retorna la referencia a la matriz actualizada
    }

    Matriz& operator-=(const Matriz& other) { // Sobrecarga del operador +=
        if (rows_ != other.rows_ || cols_ != other.cols_) {// Verifica que las dos matrices tengan el mismo tamaño
            throw std::invalid_argument("Las matrices deben tener el mismo tamaño para restarse");
        }

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                (*this)(i, j) -= other(i, j);
            }
        }
        return *this; // Retorna la referencia a la matriz actualizada
    }

private:
    size_t rows_; // Número de filas de la matriz.
    size_t cols_; // Número de columnas de la matriz.
    T* data_; // Arreglo dinámico que almacena los elementos de la matriz.
};
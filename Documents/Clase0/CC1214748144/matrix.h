#ifndef MATRIX_H
#define MATRIX_H
template<class T> class Matrix{
    public:
        Matrix(int, int);
        ~Matrix();
        void set_values();
        void get_values(int, int); 
        Matrix<T> transpuesta();
        void print();

        bool operator=(Matrix<T>); //  devuelve verdadero (1) o falso (0) si las matrices son iguales. 
        Matrix<T> operator+(Matrix<T>); // devuelve la suma de dos matrices, no modifica el objeto
        Matrix<T> operator-(Matrix<T>); // devuelve la resta de dos matrices, no modifica el objeto
        Matrix<T> operator+=(Matrix<T>); // modifica el objeto,  devuelve la suma de dos matrices
        Matrix<T> operator-=(Matrix<T>); // modifica el objeto, devuelve la resta de dos matrices
        
    private:
        int m, n;  //  filas y columnas
        T *pt; // puntero a un vector que contendrá los elementos de la matriz
};
#endif
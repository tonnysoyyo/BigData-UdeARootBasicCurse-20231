#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
template <typename T>
class Matrix {
private:
    T* matrix;
    int n, m;    
public:
    Matrix(int n, int m);//Constructor
    Matrix(const Matrix<T>& m);//Constructor para crear la matriz transpuesta
    ~Matrix();//Destructor
    void print() const;//Desplegar la matriz en la terminal
    void printTranspose() const;//Desplegra la matriz tranpuesta, pero no la crea.
    void setValue(int n, int m, T value);//asignar una valor en una posicion especifica
    T getValue(int n, int m) const;//obtener un valor de una posicion especifica.
    int GetDimN() const;//Obtener la dimension n de la matirz de forma segura
    int GetDimM() const;//obtener la dimnesion m

    Matrix<T>& operator=(const Matrix<T>& m) {//sobrecarga de la operacion "="
        if (this != &m && this->n == m.n && this->m == m.m) {
            for (int i = 0; i < (this->n*this->m); i++) {
                matrix[i] = m.matrix[i];
            }
            return *this;
        }
        else{
            cout<<"Para igualar las matrices, ambas deben tener los mismos n y m. Pero la primera matriz tiene n:"<< m.GetDimN() <<" y m:"<< m.GetDimM() <<". Mientras que la segunda matriz tiene n:"<< this->GetDimN()<< " y m:"<< this->GetDimM() <<endl;//en el caso que las matrices no tengan la misma dimension sale este mensaje.
            exit(1) ;
        }
    }
    Matrix operator+(const Matrix& m) const {//sobrecarga de la suma
        if (this->n != m.n || this->m != m.m || !matrix || !m.matrix) {//Verifica que tengan las mismas dimensiones y existan
            cout << "Las matrices no se pueden sumar. Ambas deben existir y tener las mismas dimensiones pero la primera matriz tiene n:"<< m.GetDimN() <<" y m:"<< m.GetDimM() <<". Mientras que la segunda matriz tiene n:"<< this->GetDimN()<< " y m:"<< this->GetDimM() <<endl;
            exit(1);
        }
        Matrix w(this->n,this->m);
        for (int i = 0; i < (this->n*this->m); i++) {
            w.matrix[i] = matrix[i] + m.matrix[i];
        }
        return w;
    }
    Matrix operator-(const Matrix& m) const {//sobrecarga de la resta
        if (this->n != m.n || this->m != m.m || !matrix || !m.matrix) {
            cout << "Las matrices no se pueden restar. Ambas deben existir y tener las mismas dimensiones pero la primera matriz tiene n:"<< m.GetDimN() <<" y m:"<< m.GetDimM() <<". Mientras que la segunda matriz tiene n:"<< this->GetDimN()<< " y m:"<< this->GetDimM() <<endl;
            exit(1);
        }
        Matrix w(this->n,this->m);
        for (int i = 0; i < (this->n*this->m); i++) {
            w.matrix[i] = matrix[i] - m.matrix[i];
        }
        return w;
    }
    Matrix<T>& operator+=(const Matrix<T>& m) {//sobrecraga del +=
        if (this->n != m.n || this->m != m.m || !matrix || !m.matrix) {
            cout << "Las matrices no se pueden sumar. Ambas deben existir y tener las mismas dimensiones pero la primera matriz tiene n:"<< m.GetDimN() <<" y m:"<< m.GetDimM() <<". Mientras que la segunda matriz tiene n:"<< this->GetDimN()<< " y m:"<< this->GetDimM() <<endl;
            exit(1);
        }
        for (int i = 0; i < this->n * this->m; i++) {
            matrix[i] += m.matrix[i];
        }
        return *this;
    }
    Matrix<T>& operator-=(const Matrix<T>& m) {//sobrecraga del -=
        if (this->n != m.n || this->m != m.m || !matrix || !m.matrix) {
            cout << "Las matrices no se pueden restar. Ambas deben existir y tener las mismas dimensiones pero la primera matriz tiene n:"<< m.GetDimN() <<" y m:"<< m.GetDimM() <<". Mientras que la segunda matriz tiene n:"<< this->GetDimN()<< " y m:"<< this->GetDimM() <<endl;
            exit(1);
        }
        for (int i = 0; i < this->n * this->m; i++) {
            matrix[i] -= m.matrix[i];
        }
        return *this;
    }
};
#endif
#define PARCIAL_H

#include <iostream>

using namespace std;
//Aqui se inicia a definir la clase template
template <class T> class Matrix {
    private:
        T *matrix; //Se define como privado el puntero dinamico que va a almacenar los valores cual lista plana, no se va usar doble puntero.
        int n,m;
        int size;

    public:
        
        Matrix(int n, int m);

        Matrix(const Matrix& v);

        ~Matrix();

        void setValue(int ns, int ms, T value);

        T getValue(int ng, int mg);

        int getN() const;
        int getM() const;

        void print(bool t = false);

        // Sobrecargamos los operadores: =,+,-,+=,-=

        Matrix<T>& operator=(const Matrix<T>& v);

        Matrix<T> operator+(const Matrix<T>& v) const;
        
        Matrix<T> operator-(const Matrix<T>& v) const;

        Matrix<T>& operator+=(const Matrix<T>& v);

        Matrix<T>& operator-=(const Matrix<T>& v);
    
};

// Constructor
template <class T> Matrix<T>::Matrix(int n, int m) : size(n*m) {
    this->n = n;
    this->m = m;
    matrix = new T[n*m];
    for (int i = 0; i < size; i++) {
        matrix[i] = 0.0;
    }
}

// Copy constructor
template <class T> Matrix<T>::Matrix(const Matrix& v) : size(v.n * v.m) {
    matrix = new T[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = v.matrix[i];
    }
}

// Destructor
template <class T> Matrix<T>::~Matrix(){
    delete[] matrix;
}

// Método con el cual poner valores a la Matriz
template <class T> void Matrix<T>::setValue(int ns, int ms, T value) {
    matrix[(ns*m) + ms] = value;
}

// Método con el cual obtener los valores de la Matriz
template <class T> T Matrix<T>::getValue(int ng, int mg) {
    return matrix[(ng*m) + mg];
}

// Método con el cual obtener el n (el número de filas)
template <class T> int Matrix<T>::getN() const {
    return n;
}

// Método con el cual obtener el m (el número de columnas)
template <class T> int Matrix<T>::getM() const {
    return m;
}

// Método con el cual imprimir la matriz. Si pone t = True podrá obtener la transpuesta
template <class T> void Matrix<T>::print(bool t) {
    if (t == false){
        for (int i = 0; i < n ; i++) {

            for (int j = 0; j < m; j++) {
        
                cout <<" "<< matrix[(i*m)+j] <<" ";
            }
            cout<< endl;
        }
    }
    else {
        for (int j = 0; j < m ; j++) {

            for (int i = 0; i < n; i++) {
        
                cout <<" "<< matrix[(i*m)+j] <<" ";
            }
            cout<< endl;
        }
    }
}

// Sobrecargamos el operador =
template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& v) {
    if (this != &v) {
        if (this->getN() == v.getN() && this->getM() == v.getM()) {
            delete[] matrix;
            size = v.size;
            matrix = new T[size];
            for (int i = 0; i < size; i++) {
                matrix[i] = v.matrix[i];
            }
            this->n = v.n;
            this->m = v.m;
        }
        else{
            cout << "No tienen la misma dimensión, no tiene sentido la operación" << endl;
            exit(1);
        }
    }
    return *this;
}

// Sobrecargamos el operador +
template <class T> Matrix<T> Matrix<T>::operator+(const Matrix<T>& v) const {
    if (this->getN() != v.getN() || this->getM() != v.getM()) {
        cout << "No tienen la misma dimensión, no tiene sentido la operación" << endl;
        exit(1);
    }
    Matrix w(this->getN(),this->getM());
    for (int i = 0; i < size; i++) {
        w.matrix[i] = matrix[i] + v.matrix[i];
    }
    return w;
}

// Sobrecargamos el operador -
template <class T> Matrix<T> Matrix<T>::operator-(const Matrix<T>& v) const {
    if (this->getN() != v.getN() || this->getM() != v.getM()) {
        cout << "No tienen la misma dimensión, no tiene sentido la operación" << endl;
        exit(1);
    }
    Matrix w(this->getN(),this->getM());
    for (int i = 0; i < size; i++) {
        w.matrix[i] = matrix[i] - v.matrix[i];
    }
    return w;
}

// Sobrecargamos el operador +=
template <class T> Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& v) {
    if (this != &v) {
        if (this->getN() == v.getN() && this->getM() == v.getM()) {
            for (int i = 0; i < size; i++) {
                matrix[i] += v.matrix[i];
            }
        }
        else{
            cout << "No tienen la misma dimensión, no tiene sentido la operación" << endl;
            exit(1);
        }
    }
    return *this;
}

// Sobrecargamos el operador -=
template <class T> Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& v) {
    if (this != &v) {
        if (this->getN() == v.getN() && this->getM() == v.getM()) {
            for (int i = 0; i < size; i++) {
                matrix[i] -= v.matrix[i];
            }
        }
        else{
            cout << "No tienen la misma dimensión, no tiene sentido la operación" << endl;
            exit(1);
        }
    }
    return *this;
}

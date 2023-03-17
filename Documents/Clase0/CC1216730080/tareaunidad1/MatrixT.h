#ifndef MATRIXT_H
#define MATRIXT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <optional>
#include <cmath>

using namespace std;

template<class T> class Matrix{

    private:
        int m, n;
        T *elemPtr;

    public:
        Matrix(int, int);   //ya
        ~Matrix();      //ya
        void setElement(int, int, T);   //ya
        int getM() const;       //ya
        int getN() const;       //ya
        T getElement(int, int); //ya
        void printMatrix(optional<string> message = "Imprimiendo matriz...");     //ya
        Matrix<T> transpose();

        Matrix<T>& operator=(const Matrix<T>& M){
            if (this != & M){
                if (m != M.m || n != M.n){
                    delete [] elemPtr;
                    m = M.m;
                    n = M.n;
                    elemPtr = new T[m*n];
                }
                for (int k = 0; k < m*n; k++) {
                        elemPtr[k] = M.elemPtr[k];
                }
            }
            return *this;
        }

        Matrix<T> operator+(const Matrix<T>& M) const {
            Matrix<T> w(this->m, this->n);
            for (int k = 0; k < m*n; k++) {
                    w.elemPtr[k] = this->elemPtr[k] + M.elemPtr[k];
            }
            return w;
        }

        Matrix<T> operator-(const Matrix<T>& M) const {
            Matrix<T> w(this->m, this->n);
            for (int k = 0; k < m*n; k++) {
                    w.elemPtr[k] = this->elemPtr[k] - M.elemPtr[k];
            }
            return w;
        }

        Matrix<T> & operator+=(const T& num) {
            for (int k = 0; k < m*n; k++) {
                    elemPtr[k] += num;
            }
            return *this;
        }
        
        Matrix<T> & operator-=(const T& num) {
            for (int k = 0; k < m*n; k++) {
                    elemPtr[k] -= num;
            }
            return *this;
        }

};

template<class T> Matrix<T>::Matrix(int _m, int _n){
    if (_m>0 && _n>0){
        m = _m;
        n = _n;
        elemPtr = new T[m*n];
    }
    else{
        throw out_of_range("[Matrix]Error en dimensión: m y n deben ser mayores que 0, ingresó m="+to_string(_m)+" n="+to_string(_n));
    }
}

template<class T> Matrix<T>::~Matrix(){
    //delete [] elemPtr;
    cout<<"Destruyendo objeto ..."<<endl;
}

template<class T> int Matrix<T>::getM() const{
    return m;
}

template<class T> int Matrix<T>::getN() const{
    return n;
}

template<class T> T Matrix<T>::getElement(int _i, int _j){
    if (_i<=0 || _i>m){
        throw out_of_range("[getElement]Error en dimensión: el índice de la fila debe estar entre 1 y "+to_string(m)+", ingresó i="+to_string(_i)+" j="+to_string(_j));
    }
    if (_j<=0 || _j>n){
        throw out_of_range("[getElement]Error en dimensión: el índice de la columna debe estar entre 1 y "+to_string(n)+", ingresó i="+to_string(_i)+" j="+to_string(_j));
    }
    int position = (_i-1)*n+(_j-1);
    return elemPtr[position];
}

template<class T> void Matrix<T>::setElement(int _i, int _j, T value){
    if (_i<=0 || _i>m){
        throw out_of_range("[setElement]Error en dimensión: el índice de la fila debe estar entre 1 y "+to_string(m)+", ingresó i="+to_string(_i)+" j="+to_string(_j));
    }
    if (_j<=0 || _j>n){
        throw out_of_range("[setElement]Error en dimensión: el índice de la columna debe estar entre 1 y "+to_string(n)+", ingresó i="+to_string(_i)+" j="+to_string(_j));
    }
    int position = (_i-1)*n+(_j-1);
    elemPtr[position] = value;
}

template<class T> void Matrix<T>::printMatrix(optional<string> message){
    int max_len = 0;
    for (int k=0; k<m*n; k++){
        int width = to_string(elemPtr[k]).length();
        if (width > max_len){
            max_len = width;
        }
    }
    cout<<endl;
    cout<<message.value()<<endl;
    for (int k=0; k<m*n; k++){
        int i = k/n;
        int j = k%n;
        if ((j+1)%n!=0){
            cout << setw(max_len+2) << elemPtr[k];
        }
        else{
            cout << setw(max_len+2) << elemPtr[k] << endl;
        }
    }
}

template<class T> Matrix<T> Matrix<T>::transpose(){
    Matrix<T> transposeMatrix(n, m);
    for (int i=1; i<=transposeMatrix.getM(); i++){
        for (int j=1; j<=transposeMatrix.getN(); j++){
            float value = this->getElement(j,i);
            transposeMatrix.setElement(i,j, value);
        }
    }
    return transposeMatrix;
}

#endif
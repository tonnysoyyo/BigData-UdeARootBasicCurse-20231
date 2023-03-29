#include<iostream>
#include "matrix.h"

using namespace std; 


template <class T> Matrix<T>::Matrix(int m, int n){
    this->m = m;
    this->n = n; 
    pt = new T[m*n];
}

template <class T> Matrix<T>::~Matrix(){
}


template <class T> void Matrix<T>::set_values(){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout << "Valor de la posición [" << i << "][" << j << "]: ";
            cin >> pt[i*n + j];
        }
    }
}

template <class T> void Matrix<T>::get_values(int i, int j){

    if(i < 0 || i >= m || j < 0 || j >= n){
        cout << "la posición [" << i << "][" << j << "] está fuera de rango." << endl;
        return;
    }
    else{
        cout << "EL valor en la posición [" << i << "][" << j << "] es: " << pt[i*n + j] << endl;
    }
}

template <class T> void Matrix<T>::print(){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if (j == 0){
                cout << "| ";
            } 
            if (j == n-1){
                cout << pt[i*n + j] << " |" << endl;
                continue;
            }
            else{
                cout << pt[i*n + j] << " ";
            } 
        }
        cout << endl;
    }
}

template <class T> Matrix<T> Matrix<T>::transpuesta(){
    Matrix<T> B(n, m);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            B.pt[j*m + i] = pt[i*n + j];
        }
    }
    return B;
}

template<class T> bool Matrix<T>::operator=(Matrix<T> B){
    bool val;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(pt[i*n + j] != B.pt[i*n + j]){
                val = false;
                break;
            }
            else{
                val = true;
            }
        }
    }
    
    return val;
}

template<class T> Matrix<T> Matrix<T>::operator+(Matrix<T> B){
    Matrix<T> C(m, n);
    if(m != B.m || n != B.n){
        cout << "Las matrices no tienen las mismas dimensiones." << endl;
        return C;
    }
    else{
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                C.pt[i*n + j] = pt[i*n + j] + B.pt[i*n + j];
            }
        }
    }
    return C;
}

template<class T> Matrix<T> Matrix<T>::operator-(Matrix<T> B){
    Matrix<T> C(m, n);
    if(m != B.m || n != B.n){
        cout << "Las matrices no tienen las mismas dimensiones." << endl;
        return C;
    }
    else{
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                C.pt[i*n + j] = pt[i*n + j] - B.pt[i*n + j];
            }
        }
    }
    return C;
}

template<class T> Matrix<T> Matrix<T>::operator+=(Matrix<T> B){

    if(m != B.m || n != B.n){
        cout << "Las matrices no tienen las mismas dimensiones." << endl;
        return *this;
    }
    else{
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                pt[i*n + j] = pt[i*n + j] + B.pt[i*n + j];
            }
        }
    }
    return *this;
}

template<class T> Matrix<T> Matrix<T>::operator-=(Matrix<T> B){
    if(m != B.m || n != B.n){
        cout << "Las matrices no tienen las mismas dimensiones." << endl;
        return *this;
    }
    else{
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                pt[i*n + j] = pt[i*n + j] - B.pt[i*n + j];
            }
        }
    }
    return *this;
}
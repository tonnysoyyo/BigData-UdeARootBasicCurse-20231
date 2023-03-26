#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    Matriz<int> A(2, 3);
    
    A.asignar({
    {1, 2, 5},
    {3, 4, 6}});
    
    /*A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;
    
    A[0][2] = 5;
    A[1][2] = 6;*/

    Matriz<int> B(2, 3);
    B[0][0] = 4;
    B[0][1] = 3;
    B[1][0] = 2;
    B[1][1] = 1;
    
    B[0][2] = 5;
    B[1][2] = 5;
    
    //A +=B;
    Matriz<int> C = A + B;
    Matriz<int> D = A - B;
    
    cout << "Matriz A:" << endl;
    for (int i = 0; i < A.getFilas(); i++) {
        for (int j = 0; j < A.getColumnas(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matriz B:" << endl;
    for (int i = 0; i < B.getFilas(); i++) {
        for (int j = 0; j < B.getColumnas(); j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matriz C (A + B):" << endl;
    for (int i = 0; i < C.getFilas(); i++) {
        for (int j = 0; j < C.getColumnas(); j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matriz D (A - B):" << endl;
    for (int i = 0; i < D.getFilas(); i++) {
        for (int j = 0; j < D.getColumnas(); j++) {
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Matriz (A+=C):" << endl;
    A+=C;
    for (int i = 0; i < A.getFilas(); i++) {
        for (int j = 0; j < A.getColumnas(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matriz (A-=B):" << endl;
    A-=B;
    for (int i = 0; i < A.getFilas(); i++) {
        for (int j = 0; j < A.getColumnas(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    
    
    Matriz<int> E = A.transpuesta();
    cout << "Matriz E (transpuesta de A):" << endl;
    for (int i = 0; i < E.getFilas(); i++) {
        for (int j = 0; j < E.getColumnas(); j++) {
            cout << E[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}


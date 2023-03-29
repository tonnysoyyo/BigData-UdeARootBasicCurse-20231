#include "MatrixT.h"

int main(){
    Matrix<float> A(3,3);
    A.setElement(1, 2, 1.1);
    A.setElement(2, 1, 1.2);
    A.setElement(2, 3, 1.3);
    A.setElement(3, 2, 1.4);
    A.setElement(3, 1, -1.5);
    A.setElement(1, 3, 1.5);

    cout << "El elemento en la posición 2,3 es "<<A.getElement(2,3)<<endl;
    cout << "El elemento en la posición 3,1 es "<<A.getElement(3,1)<<endl;
    cout << "El elemento en la posición 3,3 es "<<A.getElement(3,3)<<endl;
    cout << "El elemento en la posición 1,2 es "<<A.getElement(1,2)<<endl;

    A.printMatrix("Imprimiendo matriz A.");
    Matrix<float> B = A.transpose();
    B.printMatrix("Imprimiendo matriz B = A^t.");
    Matrix<float> C = A+B;
    Matrix<float> D = A-B;
    C.printMatrix("Imprimiendo A+B");
    D.printMatrix("Imprimiendo A-B");
    A += 2.0;
    A.printMatrix("Imprimiendo A+=2");
    A -= 2.0;
    A.printMatrix("Imprimiendo A-=2");
    Matrix<float> M(2,4);
    M+=M_PI;
    M.printMatrix("Matriz no cuadrada");
    return 0;
}
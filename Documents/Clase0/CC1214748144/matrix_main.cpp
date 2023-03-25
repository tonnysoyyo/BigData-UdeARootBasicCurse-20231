#include<iostream>
#include "matrix_inter.cpp"

using namespace std;


int main(){

    cout<<"*******************************"<<endl;
    cout<<" La primera matriz  A"<<endl;
    Matrix<int> A(2,2); 
    A.set_values();
    cout<<endl;
    A.print();
    cout<<endl;
    A.get_values(1, 1);
    cout<<endl;
     cout<<"*******************************"<<endl;
    cout<<" \n Transpuesta de la matriz A"<<endl;
    Matrix<int> B = A.transpuesta();
    B.print();

    //////////////////// ejecutamos la sobrecarga del =
    cout<<"*******************************"<<endl;
    cout<<" Operador = "<<endl;
    cout<<" Ingrese una nueva  matriz  D para comparar, 0 es falso y 1 es verdadero \n "<<endl;
    Matrix<int> D(2,2);
    D.set_values();
    D.print();
    cout<<"¿Es D igual a A? "<<D.operator=(A)<<endl;

    //////////////// ejecutamos sobre carga de + y -
    cout<<"*******************************"<<endl;
    cout<<" Operadores + y - no modifica los  objetos: \n"<<endl;
    cout<<"A+D: "<<endl;
    Matrix<int> obj1=D.operator+(A);
    obj1.print();
    cout<<"La matriz D sigue igual: "<<endl;
    D.print();


    cout<<"A-D: "<<endl;
    Matrix<int> obj2=D.operator-(A);
    obj2.print();
    cout<<"La matriz D sigue igual: "<<endl;
    D.print();

    //////////////////////////////// ejecutamos las sobrecargas += & -= 
     cout<<"*******************************"<<endl;
    cout<<" Operadores += y -= modifica los  objetos: "<<endl;
    cout<<"Una nueva matriz C"<<endl;
    Matrix<int> C(2,2);
    C.set_values();
    C.print();
    cout<<endl;
    cout<<"La restamos a la primera matriz A "<<endl;
    C.operator-=(A);
    cout<<"Se modifica C: "<<endl;
    C.print();
    cout<<"La sumamos a la primera matriz A "<<endl;
    C.operator+=(A);
    cout<<"Se modifica C y vuelve a ser la misma: "<<endl;
    C.print();

    return 0;
}

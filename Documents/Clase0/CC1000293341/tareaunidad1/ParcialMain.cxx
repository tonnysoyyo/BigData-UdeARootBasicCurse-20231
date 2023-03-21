#include<Parcial.h>

int main() {
    Matrix<int> intMatrix(3, 3);
    intMatrix.setValue(0, 0, 1);
    intMatrix.setValue(0, 1, 2);
    intMatrix.setValue(0, 2, 3);
    intMatrix.setValue(1, 0, 4);
    intMatrix.setValue(1, 1, 5);
    intMatrix.setValue(1, 2, 6);
    intMatrix.setValue(2, 0, 7);
    intMatrix.setValue(2, 1, 8);
    intMatrix.setValue(2, 2, 9);
    cout << "Matriz 1" << endl;
    intMatrix.print();
    //cout<<intMatrix.getValue(1,1)<<endl;
    cout<< "N: " << intMatrix.getN()<<endl;
    cout<< "M: " << intMatrix.getM()<<endl;

    Matrix<int> intMatrix2(3, 3);
    intMatrix2.setValue(0, 0, 10);
    intMatrix2.setValue(0, 1, 11);
    intMatrix2.setValue(0, 2, 12);
    intMatrix2.setValue(1, 0, 13);
    intMatrix2.setValue(1, 1, 14);
    intMatrix2.setValue(1, 2, 15);
    intMatrix2.setValue(2, 0, 16);
    intMatrix2.setValue(2, 1, 17);
    intMatrix2.setValue(2, 2, 18);
    cout << "Matriz 2" << endl;
    intMatrix2.print();
    cout<< "N: " << intMatrix2.getN()<<endl;
    cout<< "M: " << intMatrix2.getM()<<endl;
    
    //cout << "Comparación" << endl;
    //intMatrix = intMatrix2;
    //intMatrix.print();
    //intMatrix2.print();
    
    cout << "Suma" << endl;
    auto intMatrix3 = intMatrix + intMatrix2;
    intMatrix3.print();

    cout << "Resta" << endl;
    auto intMatrix4 = intMatrix - intMatrix2;
    intMatrix4.print();
/*
    cout << "Suma +=" << endl;
    intMatrix4+=intMatrix2;
    intMatrix4.print();
*/
    cout << "Resta -=" << endl;
    intMatrix4-=intMatrix2;
    intMatrix4.print();

    cout << "Transpuesta" << endl;
    bool t = true;
    intMatrix4.print(t);

    return 0;
}
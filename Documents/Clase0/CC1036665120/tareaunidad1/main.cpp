#include<iostream>

#include "Matrix.h"


int main()
{
    Matrix<int> m1(3, 4);

    m1.set(0, 0, 1);
    m1.set(0, 1, 1);
    m1.set(0, 2, 1);
    m1.set(0, 3, 1);

    m1.set(1, 0, 2);
    m1.set(1, 1, 1);
    m1.set(1, 2, 1);
    m1.set(1, 3, 1);

    m1.set(2, 0, 4);
    m1.set(2, 1, 5);
    m1.set(2, 2, 2);
    m1.set(2, 3, 9);


    m1.print();

    std::cout << " M1 --- Get Position [2,0]: " << m1.get(2,0) << std::endl;

    Matrix<int> m2(3, 4);

    m2.set(0, 0, 3);
    m2.set(0, 1, 3);
    m2.set(0, 2, 3);
    m2.set(0, 3, 3);

    m2.set(1, 0, 2);
    m2.set(1, 1, 2);
    m2.set(1, 2, 2);
    m2.set(1, 3, 2);

    m2.set(2, 0, 5);
    m2.set(2, 1, 5);
    m2.set(2, 2, 5);
    m2.set(2, 3, 6);

    m2.print();

    std::cout << "M2 --- Get Position [2,3]: " << m2.get(2,3) << std::endl;

    // add two matrices

    std::cout << " ------- ADD: M3 = M1 + M2 ------- " << std::endl;
    auto m3 = m1 + m2;
    m1.print();
    std::cout << " + " << std::endl;
    m2.print();
    std::cout << " = " << std::endl;
    m3.print();

    // subtract two matrices
    std::cout << " ------- SUBTRACT: M3 = M1 - M2 ------- " << std::endl;
    m3 = m1 - m2;
    m1.print();
    std::cout << " - " << std::endl;
    m2.print();
    std::cout << " = " << std::endl;
    m3.print();

    std::cout << " ------- EQUAL: M1 = M3 ------- " << std::endl;
    // equal two matrices
    m1 = m3;
    m3.print();
    std::cout << " = " << std::endl;
    m1.print();

    std::cout << " ------- ADD - EQUAL: M1 += M2 ------- " << std::endl;
    // equal two matrices
    m1.print();
    std::cout << " += " << std::endl;
    m2.print();
    std::cout << " = " << std::endl;
    m1 += m2;
    m1.print();


    std::cout << " ------- SUBTRACT - EQUAL: M1 -= M2 -------" << std::endl;
    // equal two matrices
    m1.print();
    std::cout << " -= " << std::endl;
    m2.print();
    std::cout << " = " << std::endl;
    m1 -= m2;
    m1.print();

    // ----------------------------
    // Error verification:

    std::cout << " ------- ERRORS -------" << std::endl;

    Matrix<int> m4(3, 2);

    m4.set(0, 0, 5);
    m4.set(0, 1, 5);

    m4.set(1, 0, 1);
    m4.set(1, 1, 1);

    m4.set(2, 0, 2);
    m4.set(2, 1, 2);


    m4.print();

    // can't get or set a position outside the dimension
    std::cout << "Get Position [3,0] in matrix 3x2: " << m4.get(3,0) << std::endl;
    std::cout << "Get Position [0,2] in matrix 3x2: " << m4.get(0,2) << std::endl;
    std::cout << "Set Position [0,2] in matrix 3x2: "; 
    m4.set(0,2,8);

    // can't add or substract: m2 is 3x3 and m4 is 3x2

    std::cout << " ------- ERRORS -------" << std::endl;
    std::cout << " Errors: Operations +, -, +=, -= " <<  std::endl;
    m1 = m2 + m4;
    m1 = m2 - m4;

    m2 += m4;
    m2 -= m4;

    return 0;
}
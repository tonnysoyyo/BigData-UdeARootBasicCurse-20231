#include <iostream>
#include "matriz.h"

int main() {
    Matriz<int> m(3, 3);// Matriz de entrada
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(0, 2) = 3;
    m(1, 0) = 4;
    m(1, 1) = 5;
    m(1, 2) = 6;
    m(2, 0) = 7;
    m(2, 1) = 8;
    m(2, 2) = 9;

    std::cout << "Matriz de entrada:" << std::endl;
    m.imprimir();

    Matriz<int> m_tr = m.transpuesta(); // Obtenemos la transpuesta de la matriz original
     std::cout << "Matriz transpuesta:" << std::endl;
     m_tr.imprimir(); // Imprimimos la matriz transpuesta 

    std::cout << "Elemento en (1, 1): " << m(1, 1) <<"\n"<< std::endl;

    m_tr = m;
     std::cout << "Matriz igual a la matriz de entrada" << std::endl;
     m_tr.imprimir();

    Matriz<int> ms = m + m_tr;
        std::cout << "Matriz igual a la matriz de entrada más la igualada a ella misma" << std::endl;
        ms.imprimir();

    Matriz<int> mm = m - m_tr;
        std::cout << "Matriz igual a la matriz de entrada menos la igualada a ella misma" << std::endl;
        mm.imprimir();

    m += m_tr;
        std::cout << "Matriz igual a la matriz de entrada más la igualada a ella misma, sobrecargada en la matriz de entrada" << std::endl;
        m.imprimir();

    m_tr -= m;
        std::cout << "Matriz igual a la igualada a la matriz de entrada menos la matriz de entrada, sobrecargada en la igualada con la de entrada" << std::endl;
        m_tr.imprimir();

     return 0;
 }

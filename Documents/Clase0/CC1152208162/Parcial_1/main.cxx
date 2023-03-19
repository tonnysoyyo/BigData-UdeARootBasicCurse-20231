#include "Matriz.h"

int main() {
	
	Matriz<int> m1(3, 2);
	
	m1.set(0, 0, 1);
	m1.set(0, 1, 2);
	m1.set(1, 0, 3);
	m1.set(1, 1, 4);
	m1.set(2, 0, 5);
	m1.set(2, 1, 6);
	
	Matriz<int> transpuesta = m1.transpuesta();
	
	Matriz<int> m2(3, 2);
	
	m2.set(0, 0, 5);
	m2.set(0, 1, 1);
	m2.set(1, 0, 7);
	m2.set(1, 1, 11);
	m2.set(2, 0, 9);
	m2.set(2, 1, 2);
	
	Matriz<int> suma = m1 + m2;
	Matriz<int> resta = m1 - m2;
	Matriz<int> igualdad = m1;
	
	cout << "M1:" << endl;
	m1.print();
	cout << "Transpuesta:" << endl;
	transpuesta.print();
	cout << "M2:" << endl;
	m2.print();
	cout << "M1 + M2:" << endl;
	suma.print();
	cout << "M1 - M2:" << endl;
	resta.print();
	cout << "M_nueva = M1:" << endl;
	igualdad.print();
	
	suma += m2;
	m1 -= igualdad;
	
	cout << "(M1 + M2) += M2:" << endl;
	suma.print();
	cout << "M1 -= M_nueva:" << endl;
	m1.print();
	
	return 0;
	}

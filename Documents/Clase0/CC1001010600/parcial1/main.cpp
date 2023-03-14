#include <iostream>
#include "matriz.h"
using namespace std;

int main(){
  cout << "Parcial 1: Programación de matrices nxn en C++" << endl;
  cout << "Ingrese las entradas de la matriz" << endl;
  Matriz<float> M(2);
  
  M.setValues(); //Solicita las entradas de la matriz
  M.getValue(1,2);//Obtiene una entrada de la matriz (fila, columna)
  
  M.printMatrix("MATRIZ"); //Imprime la matriz, recibe un string solo para fines esteticos
  
  Matriz<float> mT = M.transpose(); //Transpone la matriz y la almacena en mT
  mT.printMatrix("MATRIZ TRANSPUESTA");
  
  /*
  (M = mT).printMatrix("IGUALAR");
  (M+mT).printMatrix("SUMA");
  (M-mT).printMatrix("RESTA");
  (M += mT).printMatrix("MAS IGUAL");
  (M -= mT).printMatrix("MENOS IGUAL");
  */
  
  return 0;
}

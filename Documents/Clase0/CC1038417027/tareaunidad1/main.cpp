#include <Matrix.h>

int main(){
  // -------------------Crea 2 tipos de Matrices-----------
  /*
  cout<<"Matrix con ingreso double"<<endl;
  Matrix <double> m1(2,2);
  m1.set(0,0,1.0); 
  m1.set(0,1,2); 
  m1.set(1,0,3); 
  m1.set(1,1,4); 
  m1.mostrar_matrix();
  cout<<"Matrix con ingreso int"<<endl; 
  Matrix <int> m2(2,2);
  m2.set(0,0,0); 
  m2.set(0,1,1); 
  m2.set(1,0,2); 
  m2.set(1,1,3); 
  m2.mostrar_matrix();
  cout<<endl;
  */
  
  Matrix <int> m1(2,2); 
  m1.set(0,0,1); 
  m1.set(0,1,3); 
  m1.set(1,0,2); 
  m1.set(1,1,4);
  
  Matrix <int> m5(5,5); 
  m5.set(0,0,1); 
  m5.set(0,1,3); 
  m5.set(1,0,2); 
  m5.set(1,1,4);
  cout<<"La matriz de 5x5 es: "<<endl;
  m5.mostrar_matrix();
  cout<<endl;
  Matrix <int> m3(3,2); 
  m3.set(0,0,1); 
  m3.set(0,1,1); 
  m3.set(1,0,1); 
  m3.set(1,1,1);
  
  // -------------------Cambia una matrix por otra-----------

  //Es valido para matrices creadas con filas o columnas
  //mas grandes o mas pequeñas. 
  Matrix <int> m2(2,2); 
  //Matrix <int> m2(3,2); 
  //--------------USO DEL OPERADOR = ----------------------- 
  cout<<"Matriz original"<<endl;
  m2.mostrar_matrix(); //Muestra la matrix inicial. 
  m2 = m1; //Operador = 
  cout<<endl;
  cout<<"Matriz reemplazada"<<endl;
  m2.mostrar_matrix(); //Muestra la matrix modificada. 
  cout<<endl;
  
  // -------------------USO DEL OPERADOR + -----------------
  cout<<"La suma es: "<<endl;
  auto M1 = m2 + m1; //Crea una nueva matrix que es la suma de 2
  M1.mostrar_matrix();
  cout<<endl;
  // -------------------USO DEL OPERADOR - -----------------
  cout<<"Las matrices m1 y m3 no tienen la misma dimensión"<<endl;
  cout<<"Nos mostrara un mensaje de error"<<endl; 
  auto M2 = m1 - m3; //Crea una nueva matrix que es la resta de 2
  //Muestra un mensaje que el número de las columnas no es igual.
  cout<<endl;
  cout<<"La resta es: "<<endl;
  auto M3 = m2 - m1; 
  M3.mostrar_matrix();
  cout<<endl;
  
  
  // -------------------USO DEL OPERADOR += ----------------
  cout<<"La matrix es: "<<endl; 
  m3.mostrar_matrix();
  cout<<endl;
  m3 += 2; //Incrementa en 1 unidad todas las componentes de m3
  cout<<"Ingremento en 2: "<<endl; 
  m3.mostrar_matrix();
  cout<<endl;
  // -------------------USO DEL OPERADOR -= ---------------- 
  cout<<"Decremento en 1: "<<endl;
  m3 -= 1; //Descrementa en 1 unidad todas las componentes de m3 
  m3.mostrar_matrix();  
  cout<<endl;
  // -------------------HALLA LA TRANSPUESTA DE M2 -= ---------------- 
  //Halla la transpuesta de la matrix m2. 
  cout<<"La matrix sin transponer es: "<<endl; 
  m2.mostrar_matrix(); 
  cout<<endl;
  auto m4 = m2.tranpose();
  cout<<"La transpuesta de la matrix es: "<<endl;
  m4.mostrar_matrix();
  
} 


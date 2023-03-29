#include <cmath>
#include <iostream>

using namespace std;

template < class T> class Matriz{
private:
  T *datos;
  int dim[2];

public:


  Matriz(int filas, int columnas): dim{filas,columnas}{
      if (dim[0] > 0 && dim[1] > 0 && dim[0] == (int)dim[0] && dim[1] == (int)dim[1]) {
          datos = new T[dim[0]*dim[1]];
          for (int i = 0; i < dim[0]*dim[1]; i++) {
              datos[i] = 0;
          }
      } else {
          cout << "Error: las dimensiones deben ser enteras y positivas." << endl;
          exit(1);
      }
  }
  ~Matriz() {
    delete[] datos;
  }

  void print(){
    for(int j=1 ;j<dim[0]+1;j++){
      for(int i=1; i<dim[1]+1;i++){
        cout<<datos[dim[1]*(j-1)+i-1]<<" ";
      } 
      cout<<endl;

    }
  }

  void setvalor(int fila, int columna,double valor){
    if(fila>dim[0] || columna > dim[1]){  //verifica que fila y columna estén dentro de los valores de las dimensiones de la matriz
      cout<<"Error: dimensión errada"<<endl;
      exit(1);
    }

    datos[dim[1]*(fila-1)+columna-1]=valor;
  }

  void puntero(){
    for (int i = 0; i <dim[0]*dim[1] ; i++) {
      cout<<datos[i];
    }
    cout<<endl;
  }
  void getvalor(int fila, int columna){
    if(fila>dim[0] || columna > dim[1]){  //verifica que fila y columna estén dentro de los valores de las dimensiones de la matriz
      cout<<"Error: dimensión errada"<<endl;
      exit(1);
    }
    cout<<"la entrada de la fila "<<fila<<" y la columna "<<columna<< " es: "<<datos[dim[1]*(fila-1)+columna-1]<<endl;

  }

  Matriz<T> transpuesta(){ //Transpuesta de la matriz, cambia filas por columnas
  Matriz tr(dim[1],dim[0]);
  for(int i = 0; i < dim[1]; i++){
    for(int j = 0; j < dim[0]; j++){
      tr.datos[dim[0]*i+j]=datos[j*dim[1] + i];
    }
  }
      
   return tr; 
  }

  Matriz<T>& operator=(const Matriz<T>& mat) {
    if (this == &mat) {
      return *this;
    }
    delete[] datos;
    dim[0] = mat.dim[0];
    dim[1] = mat.dim[1];
    datos = new T[dim[0]*dim[1]];
    for (int i = 0; i < dim[0]*dim[1]; i++) {
      datos[i] = mat.datos[i];
    }
    return *this;
  }

  Matriz<T> operator+(const Matriz<T>& mat) {
    if(dim[0] != mat.dim[0] || dim[1] != mat.dim[1]){
      cout <<"Error: Las matrices no tienen las mismas dimensiones"<<endl;
      exit(1);
    }
    Matriz<T> res(dim[0], dim[1]);
    for(int i=0; i < dim[0]*dim[1]; i++){
      res.datos[i] = datos[i] + mat.datos[i];
    }
    return res;
  }

  Matriz<T> operator-(const Matriz<T>& mat) {
    if(dim[0] != mat.dim[0] || dim[1] != mat.dim[1]){
      cout <<"Error: Las matrices no tienen las mismas dimensiones"<<endl;
      exit(1);
    }
    Matriz<T> res(dim[0], dim[1]);
    for(int i=0; i < dim[0]*dim[1]; i++){
      res.datos[i] = datos[i] - mat.datos[i];
    }
    return res;
  }
  Matriz<T>& operator+=(const Matriz<T>& mat) {
    if(dim[0] != mat.dim[0] || dim[1] != mat.dim[1]){
      cout <<"Error: Las matrices no tienen las mismas dimensiones"<<endl;
      exit(1);
    }
    for(int i=0; i < dim[0]*dim[1]; i++){
      datos[i] += mat.datos[i];
    }
    return *this;
  }
  Matriz<T>& operator-=(const Matriz<T>& mat) {
    if(dim[0] != mat.dim[0] || dim[1] != mat.dim[1]){
      cout <<"Error: Las matrices no tienen las mismas dimensiones"<<endl;
      exit(1);
    }
    for(int i=0; i < dim[0]*dim[1]; i++){
      datos[i] -= mat.datos[i];
    }
    return *this;
}
};

int main()
{
    cout<<"*****************"<<endl;
    cout<<"Creamos dos matrices 2x3"<<endl;
    Matriz<double> m1(2,3);
    m1.setvalor(1,1,1);//asignación de los valores a la matriz m1
    m1.setvalor(1,2,2);
    m1.setvalor(1,3,3);
    m1.setvalor(2,1,4);
    m1.setvalor(2,2,5);
    m1.setvalor(2,3,6);
    Matriz<double> m2(2,3);
    m2.setvalor(1,1,6);//asignación de los valores a la matriz m2
    m2.setvalor(1,2,5);
    m2.setvalor(1,3,4);
    m2.setvalor(2,1,3);
    m2.setvalor(2,2,2);
    m2.setvalor(2,2,1);
    cout<<"M1:"<<endl;
    m1.print();
    cout<<endl;
    cout<<"M2:"<<endl;
    m2.print();
    cout<<endl;
    cout<<"*****************"<<endl;
    cout<<"valor de una entrada para M2"<<endl;
    m2.getvalor(1,2);
    cout<<endl;

    cout<<"*****************"<<endl;
    Matriz<double> m3(2, 2); //se crea una nueva matriz
    cout<<"suma de M1 y M2"<<endl;
    m3 = m1 + m2;
    m3.print();
    cout<<endl;

    cout<<"*****************"<<endl;
    cout<<"resta de M1 y M2"<<endl;
    m3 = m1 - m2;
    m3.print();
    cout<<endl;

    cout<<"*****************"<<endl;
    cout<<"modifiquemos M1 como la suma M1+M2"<<endl;
    m1+=m2;
    m1.print();
    cout<<"modifiquemos M1 como la resta M1-M2. Esto nos debería retornar la matriz inicial M1"<<endl;
    m1-=m2;
    m1.print();
    cout<<endl;

    cout<<"*****************"<<endl;
    cout<<"La matriz transpuesta de M1 es: "<<endl;
    Matriz<double> transpuesta = m1.transpuesta();
    transpuesta.print();

    cout<<"*****************"<<endl;
    cout<<"Si intentamos sumar o restar matrices con dimensiones diferentes: "<<endl;
    Matriz<double> m4(3,3);
    m4.setvalor(1,1,6);//asignación de los valores a la matriz m4
    m4.setvalor(1,2,5);
    m4.setvalor(1,3,4);
    m4.setvalor(2,1,3);
    m4.setvalor(2,2,2);
    m4.setvalor(2,2,1);
    m1.print();
    cout<<" + "<<endl;
    m4.print();
    m3 = m1+m4;
    m3.print();
    //Otro error: dimensiones menores que cero. Quitar el comentario para ver el error.
    //cout<<"*****************"<<endl;
    //cout<<"Si intentamos crear una matriz de dimensión (-2,3) "<<endl;
   // Matriz<double> m5(-2,3);
    return 0;
}
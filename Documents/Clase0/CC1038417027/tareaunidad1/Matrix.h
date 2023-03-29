#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

template <class T> class Matrix{

private:
  
  int size_n; //Cantidad de columnas 
  int size_m; //Cantidad de filas 
  vector <vector <T>> *v; 
  vector <vector <T>>  m_m;
  

public:
  Matrix(int n, int m):size_n(n),size_m(m){
    m_m = vector <vector <T>> (size_m);
    v = new vector<vector<T>>;  
    m_m = *v;
    for(int i=0;i<size_m;i++){
      m_m[i].resize(size_n,0);
      }
  }
  Matrix(const Matrix& m): size_n(m.size_n), size_m(m.size_m){
  	v = new vector<vector<T>>; 
  	for(int i=0; i<size_m;i++){
  		for(int j=0;j<size_n;j++){
  			v[i][j] = m.v[i][j];
  		}
  	}
  }
  ~Matrix(){
    delete v; //Elimina el puntero creado v 

  }
  void mostrar_matrix(){
    //imprimo la matriz en pantalla 
    for(int i=0; i<size_m;i++){
      cout<<"| ";
      for(int j=0;j<size_n;j++){
        cout<<m_m[i][j]<<" ";
      }
      cout<<"|"<<endl;
    }
  }  
  int getSize_fila() const{
    return size_n;
  }
  int getSize_columna() const{
    return size_m;
  }
  void set(int i, int j, T x){ 
    m_m[i][j] = x; 
  }
  T get(int i, int j) const{
    return m_m[i][j];
  }
  bool filasComparador(int i) const{
    if (i == getSize_fila()){
      return true;
    }
    else
    {
      cout<<"ERROR: El número de filas entre las matrices no es igual"<<endl;
      return false;
    }
  }
  bool columnaComparador(int i) const{
    if (i == getSize_columna()){
      return true;
    } 
      
    else
    {
      cout<<"ERROR: El número de columnas entre las matrices no es igual"<<endl;
      return false;
    }    
  }
  
  Matrix <T> & operator=(const Matrix& m){
    if(this != &m){
      if (size_m != m.size_m or size_n != m.size_n){
        delete v; 
        size_n = m.size_n; 
        size_m = m.size_m; 
        v = new vector<vector<T>>;
      }
      for(int i=0; i<size_m;i++){
        for(int j=0;j<size_n;j++){
          set(i,j,m.get(i,j));
        }
      }
    }
    return *this;
  }
  Matrix <T>  operator+(const Matrix& m) const{
    Matrix<T>  w(size_n,size_m);
    if(filasComparador(m.size_n) and columnaComparador(m.size_m)){
      for (int i=0;i<size_m;i++){
        for (int j=0;j<size_n;j++){
          w.m_m[i][j] = m_m[i][j] + m.m_m[i][j];
        }
      }
      return w; 
    }
    else{
    	return w; 
    }
  }
  Matrix <T>  operator-(const Matrix& m) const{
    Matrix w(size_n,size_m); 
    if(filasComparador(m.size_n) and columnaComparador(m.size_m)){
	    for (int i=0;i<size_m;i++){
	      for (int j=0;j<size_n;j++){
	        w.m_m[i][j] = m_m[i][j] - m.m_m[i][j];
	      }
	    }
    	return w;
    }
    else{
    	return w;
    }
  }
  Matrix <T>  operator+=(const T cantidad){
    Matrix w(size_n,size_m); 
    for (int i=0; i<size_m;i++){
      for (int j=0; j<size_n;j++){
        w.set(i,j,get(i,j) + cantidad);   
        set(i,j,get(i,j) + cantidad); 
      }
    }
    return w;

  }
  Matrix <T>  operator-=(const T cantidad){
    Matrix w(size_n,size_m); 
    for (int i=0; i<size_m;i++){
      for (int j=0; j<size_n;j++){
        w.set(i,j,get(i,j) - cantidad);   
        set(i,j,get(i,j) - cantidad); 
      }
    }
    return w;
  }
  Matrix <T> tranpose(){
      Matrix <T> w(size_m,size_n);
      for (int i=0; i<size_m;i++){
        for(int j=0; j<size_n;j++){
          w.m_m[j][i] = m_m[i][j];
        }
      }
      return w;
  }
};

#endif
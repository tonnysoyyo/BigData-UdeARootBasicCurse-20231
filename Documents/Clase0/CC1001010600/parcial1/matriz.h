#include <iostream>
using namespace std;

template<class T> class Matriz{

  public:
  //Constructor
  Matriz(int n){
    this->n = n;
    mat = new T[n*n];
  }

  //Destructor
  ~Matriz(){
    delete [] mat;
    mat = NULL;
  }

  /*Solicita las entradas de la matriz
    Lee la matriz como una lista
   */
  void setValues(){
    int f = 1, c = 1;
    //For para obtener los valores de la matriz
      for(int j=0; j<n*n; j++){
	cout << "P_" << f << "," << c << ": ";
	cin >> mat[j];
	
	//Para cambiar de fila y columna en el cout
	c++;
	
	if((j+1)%n == 0){
	  f++; c = 1;
	}
      }
  }
  
  //Obtiene el valor r,c de la matriz usando (r-1) * n + c - 1 
  void getValue(int r, int c){
    if( ( (r-1) * n + c - 1 ) <= n*n )
      cout << endl << "P_" << r << "," << c << "= " << mat[ (r-1) * n + c - 1] << endl;
    else{
      cout << "Esta posicion no existe" << endl;
    }
  }

  //Imprime la matriz
  void printMatrix(string name){
    cout << "*****************" << endl;
    cout << name << endl;
    cout << "*****************" << endl;
    for(int j=0; j<n*n; j++){
      cout << mat[j] << "\t";
	
      if((j+1)%n == 0){
	cout << endl;
      }
    }
    cout << "*****************" << endl;
  }

  //Retorna un objeto de la clase correspondiente a la matriz transpuesta
  Matriz<T> transpose(){
    Matriz<float> mT(n);
    mT.mat = new T[n*n];
    
    int j = 0, k = 1;
    for(int i = 0; i<n*n; i++){
	mT.mat[i] = mat[j];
	//Contadores auxiliares para recorrer los valores de la matriz original
	j+=n;
	  if(j>=n*n){
	    j = k; k++;
	  }
    }
    return mT;
  }

  
  //Sobre carga de operadores

  Matriz<T> operator+(Matriz<T> &s1){
    Matriz<float> S(n);
    S.mat = new T[n*n];
    
    if(n != s1.n ){
      throw invalid_argument("Matrices de distinta dimension");
    }
    else{
      for(int i = 0; i<n*n; i++){
        S.mat[i] = mat[i] + s1.mat[i];
      }
      return S;
    }   
  }

  Matriz<T> operator-(Matriz<T> &s1){
    Matriz<float> S(n);
    S.mat = new T[n*n];
    
    if(n != s1.n ){
      throw invalid_argument("Matrices de distinta dimension");
    }
    else{
      for(int i = 0; i<n*n; i++){
        S.mat[i] = mat[i] - s1.mat[i];
      }
      return S;
    }   
  }

  Matriz<T>& operator=(Matriz<T> &I){
    if(this != &I){
      if(n != I.n){
	delete [] mat;
	mat = new T[I.n * I.n];
      }
      for(int i = 0; i< I.n*I.n; i++){
	mat[i] = I.mat[i];
      }
    }
    return *this;
  }

  Matriz<T>& operator+=(Matriz<T> &MI){
    if(n != MI.n ){
      throw invalid_argument("Matrices de distinta dimension");
    }
    else{
      for(int i = 0; i< n*n; i++){
	mat[i] += MI.mat[i];
      }
      return *this;
    }
  }

  Matriz<T>& operator-=(Matriz<T> &MI){
    if(n != MI.n ){
      throw invalid_argument("Matrices de distinta dimension");
    }
    else{
      for(int i = 0; i< n*n; i++){
	mat[i] -= MI.mat[i];
      }
      return *this;
    }
  }
  
  private:  
  int n{0};
  T* mat = NULL;
};

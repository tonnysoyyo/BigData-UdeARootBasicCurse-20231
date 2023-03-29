#include<iostream>
#include<cmath>
using namespace std;

template<class T> class Matriz{
    
private:
    int NoCol; //Número de columnas
    int NoRow; //Número de filas
    T* element; //Elementos de la matriz, establecidos enun conjunto horizontal
    int size; //tamaño de la matriz

public:
    
    //Constructor de una matriz de ceros con n filas, n columnas
    // Si se estable int n recorta los decimales a discreción por lo que se decidió hacer lo siguiente:
    Matriz(float n, float m){
        if(floor(n) - n != 0 || floor(m) - m != 0){
            cout<<"ConstructorWarning: Los índices decimales se cambiaron a su parte entera"<<endl;
        } 
        this->NoCol=floor(m);
        this->NoRow=floor(n);
        if(n>=0 && m>=0){
            this->size=NoCol*NoRow;
            element = new T[size];
            for (int i = 0; i < size; i++) {
                element[i] = 0;
            }
        }
    }
    //Copy constructor
    Matriz(const Matriz<T>& M) : size(M.size), NoRow(M.NoRow), NoCol(M.NoCol) {
        element = new T[size];
        for (int i = 0; i < size; i++) {
            element[i] = M.element[i];
        }
    }

    
    
    //Destructor 
    ~Matriz(){
        delete[] element;
    }

    //Obtener el elemento n,m
    T get(float N, float M) {
        if(floor(N) - N != 0 || floor(M) - M != 0){
            cout<<"GetWarning: Los índices decimales se cambiaron a su parte entera"<<endl;
        }
        int n = floor(N);
        int m = floor(M);
        //índice correspondiente en el arreglo horizontal correspondiente a n,m:
        if(n<NoRow && m<NoCol  && n>=0 && m>=0){
            int ind = NoCol*n+m; 
            return element[ind];
        }else{
            cout<<"GetError: El índice no existe"<<endl;
            exit(1);
        }
    }

    //Cambiar el valor del elemento n,m
    void set(float N, float M, T x) {
        if(floor(N) - N != 0 || floor(M) - M != 0){
            cout<<"SetWarning: Los índices decimales se cambiaron a su parte entera"<<endl;
        }
        int n = floor(N);
        int m = floor(M);
        if(n<NoRow && m<NoCol && n>=0 && m>=0){
            int ind = NoCol*n+m;
            element[ind]=x;
        }else{
            cout<<"SetError: El índice no existe"<<endl;
            exit(1);
        }
    }
    
    //imprimir la matriz por filas
    void mostrar(){
        for(int i=0; i < NoRow; i++){
            for(int j=0; j < NoCol; j++){
                cout<<get(i,j)<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    //Obtener la transpuesta de la matriz
    //Toma los elementos por columnas y los reescribe uno a uno en
    //otra matriz Trans de m filas y n columnas
    Matriz<T> transpuesta(){
        Matriz<T> Trans(NoCol,NoRow);
        for(int j = 0; j < NoCol; j++){
            //va selecccionando los valores de la columna j
            for(int i = 0; i < NoRow; i++){     
                //Asigna los valores de la fila i en Trans         
                Trans.set(j, i, get(i, j));
            };
        }  
        return Trans;  
    }

    //SOBRECARGA DE OPERADORES:
    Matriz<T>& operator=(const Matriz<T>& M){
        if (this != &M){
            if (NoCol == M.NoCol && NoRow == M.NoRow) {
                element = new T[NoCol*NoRow];
                for(int i=0;i<size;i++){
                    element[i]=M.element[i];
                }
            }else{
                cout<<"IgualError: Las dimensiones no concuerdan"<<endl;
                exit(1);
            }
        }
        return *this;
        
    }

    Matriz<T> operator+(const Matriz<T>& M) const{
        if(NoCol == M.NoCol && NoRow == M.NoRow){
            Matriz<T> S(NoRow, NoCol);         
            for (int i = 0; i < size; i++) {
                S.element[i]= element[i] + M.element[i];
            }
            return S;
            
        }else{
            cout<<"SumaError: Las dimensiones no concuerdan"<<endl;
            exit(1);
        }
    }

    Matriz<T> operator-(const Matriz<T>& M) const{
        if(NoCol == M.NoCol && NoRow == M.NoRow){
            Matriz<T> S(NoRow, NoCol);         
            for (int i = 0; i < size; i++) {
                S.element[i]= element[i] - M.element[i];
            }
            return S;
            
        }else{
            cout<<"RestaError: Las dimensiones no concuerdan"<<endl;
            exit(1);
        }
    }
    
    void operator+=(const Matriz<T>& M) const{
        if(NoCol == M.NoCol && NoRow == M.NoRow){       
            for (int i = 0; i < size; i++) {
                element[i]= element[i] + M.element[i];
            }
            
        }else{
            cout<<"Suma'Error: Las dimensiones no concuerdan"<<endl;
            exit(1);
        }
    }

    void operator-=(const Matriz<T>& M) const{
        if(NoCol == M.NoCol && NoRow == M.NoRow){       
            for (int i = 0; i < size; i++) {
                element[i]= element[i] - M.element[i];
            }
            
        }else{
            cout<<"Resta'Error: Las dimensiones no concuerdan"<<endl;
            exit(1);
        }
    }
        
};

int main()
{   
    cout<<"Hacer una matriz A de ceros:"<<endl;
    Matriz<int> A(2,3);
    A.mostrar();
    
    cout<<"Rellenarla:"<<endl;
    A.set(0.1,1,1);
    A.set(0,2,2);
    A.set(1,0,3);
    A.set(1,1,4);
    A.set(1,2,5);
    A.mostrar();

    cout<<"Elemento (0,2) de A: "<<A.get(0,2)<<endl<<endl;


    Matriz<int> B=A.transpuesta();
    cout<<"La transpuesta de A es B:"<<endl;
    B.mostrar();

    Matriz<int> C=B.transpuesta();
    cout<<"La transpuesta de B es C, con los mismos elementos que A:"<<endl;
    C.mostrar();

    A.set(1,2,3);
    cout<<"Puedo cambiar nuevamente un elemento de A:"<<endl;
    A.mostrar();

    C=A;
    cout<<"Puedo igualar C con A:"<<endl;
    C.mostrar();

    cout<<"Cambiar A no cambia C:"<<endl;
    A.set(1,2,5);
    cout<<"A:"<<endl;
    A.mostrar();
    cout<<"C:"<<endl;
    C.mostrar();

    cout<<"Puedo hacer A+=C, cambiando el valor de A:"<<endl;
    A+=C;
    A.mostrar();

    cout<<"Si hago A-=C, A vuelve a su estado anterior:"<<endl;
    A-=C;
    A.mostrar();

    cout<<"O puedo hacer otra matriz D igual a A-C"<<endl;
    auto D=A-C;
    D.mostrar();

    cout<<"Y otra E igual a A+C"<<endl;
    auto E=A+C;
    E.mostrar();

    return 0;
}

#include<iostream>

using namespace std;
// Clase Matriz n x m
template<class Temp> class Matrix {

private:
    
    // Atributos de cada objeto
    Temp* Data; // Puntero con valores de la Matriz
    int Dim[2]; // {n,m}

public:
    
    // Constructor
    Matrix(int Dim_n, int Dim_m) {
        
        if((Dim_n <= 0) || (Dim_m <= 0)) {
            
            cout<<"----Dimensiones de la matriz no son validas----"<<endl;
            cout<<"----Se llama a bad_array_new_length----"<<endl;
            
        }
        cout<<"----Inicializando Clase Template Matrix----"<<endl;

        // Definir dimensiones
        Dim[0] = Dim_n;
        Dim[1] = Dim_m;

        Data = new Temp[Dim[0]*Dim[1]]; // Inicializando

        // Por defecto la Matriz se llena de ceros
        for (int i = 0; i < Dim[0]*Dim[1]; i++) {
            Data[i] = 0;
        }
 
    }
    // Copy Constructor
    Matrix(const Matrix<Temp>& M) {

        cout<<"----Inicializando Clase Template Matrix----"<<endl;
        Dim[0] = M.Dim[0];
        Dim[1] = M.Dim[1];

        Data = new Temp[Dim[0]*Dim[1]];

        // Copiando Matriz
        for (int i = 0; i < Dim[0]*Dim[1]; i++) {
            Data[i] = M.Data[i];
        }


        
    }
    // Destructor
    ~Matrix(){
        delete[] Data;
    }

    // Dimensión n
    int GetDimY() const{
        return Dim[0];
    }

    // Dimensión n
    int GetDimX() const{
        return Dim[1];
    }

    // Posición (i,j) (Comenzando en 0)
    Temp M_ij(int i, int j) const {
        return Data[i*Dim[1]+j];
    }

    // Imprimir Matrix
    void VerMatrix(){
    for (int k = 0; k<Dim[0] ; k++){
            for (int l = 0; l<Dim[1] ; l++) {
                cout<<M_ij(k,l)<<"   ";
            }
        cout<<endl;
    }
    }

    // Definir Posición (i,j) (Comenzando en 0)
    void SetM_ij(int i, int j, Temp Valor){
        Data[i*Dim[1]+j] = Valor;
    }

    // Sobrecarga de Operadores

    // Operador igual, es una especie de copia de un objeto de la clase
    Matrix<Temp>& operator=(const Matrix<Temp>& M) {
        if (this != &M) {
                if ((Dim[0] != M.Dim[0])||(Dim[1] != M.Dim[1])) {
                delete[] Data;
                Dim[0] = M.Dim[0];
                Dim[1] = M.Dim[1];
                Data = new Temp[Dim[0]*Dim[1]];
            }
            for (int k = 0; k<Dim[0] ; k++){
                for (int l = 0; l<Dim[1] ; l++) {
                    SetM_ij(k,l,M.M_ij(k,l));
                }
            }
        }
        return *this;
    }
    // Suma dos Matrices
    Matrix<Temp> operator+(const Matrix<Temp>& M) const {
        Matrix<Temp> M_result(Dim[0],Dim[1]);
        Temp Val;
        
        for (int k = 0; k<Dim[0]; k++) {
            for (int l=0; l< Dim[1]; l++){
                Val = M_ij(k,l) + M.M_ij(k,l);
                M_result.SetM_ij(k,l,Val);
            }
            
        }

        return M_result;
    }
    // Resta dos Matrices
    Matrix<Temp> operator-(const Matrix<Temp>& M) const {
        Matrix<Temp> M_result(Dim[0],Dim[1]);
        double Val;
        
        for (int k = 0; k<Dim[0]; k++) {
            for (int l=0; l< Dim[1]; l++){
                Val = M_ij(k,l) - M.M_ij(k,l);
                M_result.SetM_ij(k,l,Val);
            }
            
        }

        return M_result;
    }
    
    // Suma N a cada elemento de la Matriz
    Matrix<Temp>& operator+=(const Temp N) {
        Temp Val;

        for (int k= 0; k<Dim[0]; k++) {
            for (int l= 0; l< Dim[1]; l++){
                Val = M_ij(k,l) + N;
                SetM_ij(k,l,Val);
            }
            
        }
        return *this;
    }

    // Resta N a cada elemento de la Matriz, se utiliza el operador +=
    Matrix<Temp>& operator-=(const Temp N) {return *this += -1*N;}
    
    // Matriz Traspuesta
    Matrix<Temp> Traspuesta() const {
        Matrix<Temp> M_T(Dim[1],Dim[0]);
        double Val;

        for(int k=0;k<Dim[0];k++){
            for(int l=0; l<Dim[1]; l++){
                Val = M_ij(k,l);
                M_T.SetM_ij(l,k,Val);
            }
        }
        return M_T;

    }

};

    int main(){
    

    // ----Tests----
    // (Descomentar las líneas para probar)

    // // ---Dimensiones negativas---
    // // Veamos lo que sucede al intentar inicializar una matriz con dimensiones negativas:

    // Matrix<double> Matriz_A(4,-5);

    // // ---------------------------

    // // ---Probando Constructor---
    // Matrix<double> Matriz_A(4,5);
    // // ---------------------------

    // // ---Probando Copy Constructor---
    // Matrix<double> Matriz_A(4,5);
    // Matrix Matriz_B(Matriz_A);
    // // ---------------------------

    // // ---Probando Métodos para Obtener Dimensiones de Matriz---
    // Matrix<double> Matriz_A(4,5);
    // cout<<"Dimensión en Y (n)= "<<Matriz_A.GetDimY()<<endl;
    // cout<<"Dimensión en X (m)= "<<Matriz_A.GetDimX()<<endl;
    // // ---------------------------

    // // ---Probando Método para Obtener Posición (i,j)---
    // Matrix<double> Matriz_A(4,5);
    // int i = 3,j=4;
    // cout<<"Posición ("<<i<<","<<j<<") = "<<Matriz_A.M_ij(i,j)<<endl;
    // // ---------------------------

    // // ---Probando Método para Imprimir Matriz---
    // Matrix<double> Matriz_A(4,5);
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();
    // // ---------------------------

    // // ---Probando Método para Definir Posición (i,j)---
    // Matrix<double> Matriz_A(4,5);
    // int i = 3,j=4;

    // cout<<"-----Antes-----"<<endl;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();

    // cout<<"-----Después-----"<<endl;
    // double valor = 17.5;
    // Matriz_A.SetM_ij(i,j,valor);
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();
    // // ---------------------------

    // // ---------------------------

    // Sobrecarga de Operadores 

    // // ---Probando Operador = ---
    // Matrix<double> Matriz_A(4,5);
    // Matrix<double> Matriz_B(4,5);
    // int i = 3,j=4;
    // double valor = 17.5;
    // Matriz_A.SetM_ij(i,j,valor);

    // cout<<"-----Antes-----"<<endl;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();
    // cout<<"---Matriz B---"<<endl;
    // Matriz_B.VerMatrix();

    // cout<<"-----Después-----"<<endl;

    // Matriz_B = Matriz_A;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();
    // cout<<"---Matriz B---"<<endl;
    // Matriz_B.VerMatrix();
    // // ---------------------------

    // // ---Probando Operador + ---
    // Matrix<double> Matriz_A(4,5);
    // Matrix<double> Matriz_B(4,5);
    // int i = 3,j=4;
    // double valor = 17.5;
    // Matriz_A.SetM_ij(i,j,valor);
    // Matriz_A.SetM_ij(i-2,j,valor*2);
    // Matriz_A.SetM_ij(i,j-1,valor-10.0);
    // Matriz_A.SetM_ij(i-2,j-3,valor+0.1);

    // Matriz_B.SetM_ij(i,j,-1.0*valor);
    // Matriz_B.SetM_ij(i-3,j,valor/2);
    // Matriz_B.SetM_ij(i-2,j-1,valor+10.0);
    // Matriz_B.SetM_ij(i-1,j-1,valor-0.1);

    // cout<<"-----Antes-----"<<endl;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();
    // cout<<"---Matriz B---"<<endl;
    // Matriz_B.VerMatrix();

    // cout<<"-----Después-----"<<endl;

    // Matrix Matriz_C = Matriz_A + Matriz_B;
    // cout<<"---Matriz C---"<<endl;
    // Matriz_C.VerMatrix();
    // // ---------------------------

    // // ---Probando Operador - ---
    // Matrix<double> Matriz_A(4,5);
    // Matrix<double> Matriz_B(4,5);
    // int i = 3,j=4;
    // double valor = 17.5;
    // Matriz_A.SetM_ij(i,j,valor);
    // Matriz_A.SetM_ij(i-2,j,valor*2);
    // Matriz_A.SetM_ij(i,j-1,valor-10.0);
    // Matriz_A.SetM_ij(i-2,j-3,valor+0.1);

    // Matriz_B.SetM_ij(i,j,-1.0*valor);
    // Matriz_B.SetM_ij(i-3,j,valor/2);
    // Matriz_B.SetM_ij(i-2,j-1,valor+10.0);
    // Matriz_B.SetM_ij(i-1,j-1,valor-0.1);

    // cout<<"-----Antes-----"<<endl;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();
    // cout<<"---Matriz B---"<<endl;
    // Matriz_B.VerMatrix();

    // cout<<"-----Después-----"<<endl;

    // Matrix Matriz_C = Matriz_A - Matriz_B;
    // cout<<"---Matriz C---"<<endl;
    // Matriz_C.VerMatrix();
    // // ---------------------------

    // // ---Probando Operador += ---
    // Matrix<double> Matriz_A(4,5);
    // double valor = 1.41;
    // int i = 3,j=4;
    // Matriz_A.SetM_ij(i,j,valor);

    // cout<<"-----Antes-----"<<endl;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();

    // cout<<"-----Después-----"<<endl;
    // Matriz_A += valor;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();
    // // ---------------------------

    // // ---Probando Operador -= ---
    // Matrix<double> Matriz_A(4,5);
    // double valor = 1.41;
    // int i = 3,j=4;
    // Matriz_A.SetM_ij(i,j,valor);

    // cout<<"-----Antes-----"<<endl;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();

    // cout<<"-----Después-----"<<endl;
    // Matriz_A -= valor;
    // cout<<"---Matriz A---"<<endl;
    // Matriz_A.VerMatrix();
    // // ---------------------------


    return 0;
    }
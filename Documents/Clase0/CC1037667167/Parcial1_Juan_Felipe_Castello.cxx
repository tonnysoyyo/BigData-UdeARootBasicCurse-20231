#include<iostream>
#include<stdlib.h>
#include <stdexcept>
#include<cstring>

using namespace std;

template<class TypeData>
class Matrix{

    private: /*Encapsulamiento de atributos.*/
    int Nrows , Ncols;
    TypeData *Array_Matrix;

    public:
    /*Constructores---------*/
    Matrix(){
        Nrows = 0;
        Ncols = 0;
        Array_Matrix = nullptr;
    }
    /*Constructor con dos parametros:*/
    Matrix(int _Nrows , int _Ncols){
        if (_Ncols < 0 || _Nrows < 0){throw std::invalid_argument( "Error!, Las matrices no tienen filas o columnas negativas!!" );}
        this -> Nrows = _Nrows;
        this -> Ncols = _Ncols;
        Array_Matrix = new TypeData [Nrows * Ncols];
        for(int i = 0 ; i<Nrows * Ncols ; i++){Array_Matrix[i] = 0.0;}
    }
    /*Copy constructor:*/
    Matrix ( const Matrix &_M){
        this -> Nrows = _M.Nrows ; 
        this -> Ncols = _M.Ncols;
        Array_Matrix = new TypeData [Nrows * Ncols];
        for(int i = 0 ; i<Nrows * Ncols ; i++){*(Array_Matrix + i) = *(_M.Array_Matrix + i);}
    }

    void Set_Values(){
         for (int i = 0 ; i<Nrows ; i++){
            for (int j = 0 ; j<Ncols; j++){
                cout<<"Ingrese el valor en la posición ["<<i<<"]["<<j<<"]:  "; 
                cin>>*(Array_Matrix + Ncols*i + j);}}

        }
    /*---------------------------------------------------------------------------------------------------------------------*/

    TypeData Get_Pos_Value(int row , int col){
        if(row >= Nrows || col >= Ncols){throw std::invalid_argument( "Error!, indice fuera de rango!" );}
        else{return *(Array_Matrix + Ncols*row + col) ;}}

    TypeData *Get_Array(){ /*Método para retornar un puntero que "apunta a la matriz"*/
        return Array_Matrix;};

    int Get_Nrows(){
        return Nrows;}

    int Get_Ncols(){
        return Ncols;}

    void Print_Matrix(){
        for (int i = 0 ; i<Nrows ; i++){
            cout<<endl;
            for (int j = 0 ; j<Ncols ; j++){
                cout<<*(Array_Matrix + Ncols*i + j)<<" ";}}cout<<endl;}

    /*Sobrecarga de operadores --------------------------------------------------------------------------------------------*/
    Matrix operator = (const Matrix &Matrix_object){

        delete [] Array_Matrix;
        this -> Nrows = Matrix_object.Nrows;
        this -> Ncols = Matrix_object.Ncols;
        Array_Matrix = new TypeData [Nrows * Ncols];

        for (int i = 0 ; i<Nrows*Ncols ; i++){Array_Matrix [i] = Matrix_object.Array_Matrix[i];}

        return *this;
    }

    Matrix operator + (const Matrix &Matrix_object)const{

        if(Matrix_object.Nrows != Nrows || Matrix_object.Ncols != Ncols)
        {throw std::invalid_argument("Matrices de diferente tamaño no se pueden sumar" );}

        
        Matrix <TypeData> Temp(Nrows,Ncols); Temp.Nrows = Nrows ; Temp.Ncols = Ncols;
        for(int i = 0 ; i<Nrows*Ncols; i++){
                //Temp.Array_Matrix[i] = Array_Matrix[i] + Matrix_object.Array_Matrix[i];
                *(Temp.Array_Matrix +i) = *(Array_Matrix +i) + *(Matrix_object.Array_Matrix + i);} 
                return Temp;}

   Matrix operator - (const Matrix &Matrix_object)const{

        if(Matrix_object.Nrows != Nrows || Matrix_object.Ncols != Ncols)
        {throw std::invalid_argument("Matrices de diferente tamaño no se pueden restar" );}

        Matrix <TypeData> Temp(Nrows,Ncols); Temp.Nrows = Nrows ; Temp.Ncols = Ncols;
        for(int i = 0 ; i<Nrows*Ncols; i++){
                //Temp.Array_Matrix[i] = Array_Matrix[i] - Matrix_object.Array_Matrix[i];
                *(Temp.Array_Matrix +i) = *(Array_Matrix +i) - *(Matrix_object.Array_Matrix + i);}

        return Temp;}

    Matrix operator += (const TypeData num){

        Matrix <TypeData> Temp(Nrows,Ncols); Temp.Nrows = Nrows ; Temp.Ncols = Ncols;
            for(int i = 0 ; i<Nrows*Ncols; i++){
                    Temp.Array_Matrix[i] =  Array_Matrix[i]  + num ;} return Temp;}

    Matrix operator -= (const TypeData num){

        Matrix <TypeData> Temp(Nrows,Ncols); Temp.Nrows = Nrows ; Temp.Ncols = Ncols;
            for(int i = 0 ; i<Nrows*Ncols; i++){
                    Temp.Array_Matrix[i] =  Array_Matrix[i]- num ;} return Temp;}


    Matrix Transpuesta(){

        Matrix <TypeData> Temp(Nrows,Ncols); Temp.Nrows = Ncols ; Temp.Ncols = Nrows;        
        for (int i = 0 ; i<Nrows ; i++){
            for (int j = 0 ; j<Ncols ; j++){ 
                *(Temp.Array_Matrix + i + Nrows*j) = *(Array_Matrix + Ncols*i + j); }}return Temp ;}

   ~Matrix(){ delete[] Array_Matrix;} //Destructor.

};

int main(){
    int r1 , c1; cout<<"Ingrese numero de filas y columnas (Separados por un enter):  "; cin>>r1>>c1;
    Matrix <float> My_Matrix(r1 , c1);
    My_Matrix.Set_Values();
    My_Matrix.Print_Matrix();

    
    cout<<"Probando el metodo Get_pos_value(): "<<endl;
    int row , col; cout<<"ingrese posicion i,j de la cual desea conocer el valor (Separador por un enter):"; cin>>row>>col;
    cout<<"El ejelmento ["<<row<<"]["<<col<<"] = "<<My_Matrix.Get_Pos_Value(row , col) <<endl;

    cout<<"Probando el metodo Get_Array(), Imprimamos la matriz fuera de la clase solo para comprobarlo: "<<endl;

     for (int i = 0 ; i<My_Matrix.Get_Nrows() ; i++){
        cout<<endl;
        for (int j = 0 ; j<My_Matrix.Get_Ncols() ; j++){
            cout<<*(My_Matrix.Get_Array() + My_Matrix.Get_Ncols()*i + j)<<" ";}} 

    
    cout<<endl;
    int r2 , c2; cout<<"Probando la suma de matrices, definamos otra matriz, ingrese numero de filas y columnas,(Separados por un enter):   "<<endl; cin>>r2>>c2;
    Matrix <float> My_Matrix2(r2,c2);
    My_Matrix2.Set_Values();
    My_Matrix2.Print_Matrix();

  
    auto My_Matrix3 = My_Matrix + My_Matrix2;
    cout<<"La suma es:  "<<endl;
    My_Matrix3.Print_Matrix();
    cout<<endl;
    
    cout<<"Probando la resta de matrices:  "<<endl;
    auto My_Matrix4 = My_Matrix - My_Matrix2;
    cout<<"La resta es:  "<<endl;
    My_Matrix4.Print_Matrix();
    cout<<endl; 

    cout<<"Probando la Igualacion de objetos matrices:"<<endl;
    My_Matrix4 = My_Matrix3;
    cout<<"El valor de la matriz resta ahora es: "<<endl;
    My_Matrix4.Print_Matrix();
    cout<<endl<<" Que en efecto coincide con el valor de la matriz suma!: "<<endl;

    cout<<"Probando la sobrecarga +=:"<<endl;
    int num ; cout<<"Ingrese un número entero:  ";cin>>num;
    (My_Matrix4 += num).Print_Matrix();

    cout<<"Probando la sobrecarga -=:"<<endl;
    int num1 ; cout<<"Ingrese un número entero:  ";cin>>num;
    auto My_Matrix5 = (My_Matrix4 -= num);
    My_Matrix5.Print_Matrix();
    
    cout<<"Probando la transpuesta (Apliquemosa a la anterior matriz):  "<<endl;
    My_Matrix5.Transpuesta().Print_Matrix();
    

  

    return 0;}



    



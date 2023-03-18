#include<Matrix.h>

template <typename T>
    Matrix<T>::Matrix(int n, int m) {//aqui se define el puntero dinamico que almacenara los valores
        this->n = n;
        this->m = m;
        matrix = new T[n*m]; //Como no se puede usar doble puntero se usara un arreglo de dimensiones 1X(n*m) "1 fila y n*m columnas"
    }
    template <typename T>//Este es el metodo encargado de crear la matriz transpuesta.
    Matrix<T>::Matrix(const Matrix<T>& w) {
        this->n = w.m;//Aqui se invierten las dimensiones
        this->m = w.n;
        matrix = new T[this->n*this->m];
        // copiar elementos de la matriz transpuesta
        for (int i = 0; i < this->n ; i++) {        
            for (int j = 0; j < this->m; j++) {            
                matrix[(i*this->m)+j] = w.matrix[(j*this->n)+i];
            }

        }
    }
    template <typename T>
    void Matrix<T>::print() const{//Debido a que se esta trabajando con un array de 1x(n*m) se define la forma de mostrar la matriz al usuario de la siguente;
        for (int i = 0; i < n ; i++) {        
            for (int j = 0; j < m; j++) {            
                cout <<" "<< matrix[(i*m)+j] <<" ";
            }
            cout<< endl;
        }
    }
    template <typename T>
    void Matrix<T>::printTranspose() const{//Debido a que se esta trabajando con un array de 1x(n*m) se define la forma de mostrar la matriz al usuario de la siguente;
        for (int i = 0; i < m ; i++) {        
            for (int j = 0; j < n; j++) {            
                cout <<" "<< matrix[(j*m)+i] <<" ";
            }
            cout<< endl;
        }
    }
    template <typename T>
    void Matrix<T>::setValue(int ns, int ms, T value) {//Se define la funcion para asignar valor a cada posicion de la lista, se usa "ns" y "ms" a forma de "n y m de la funcion Set" para diferenciar los del n y m de la dimension del array    
        if (ns>=this->n || ms>=this->m){
            cout<<"La ubicacion ingresada en el setValue no es valida, por favor tenga en cueta que la matriz es de dimenciones n="<<this->n<<" y m="<<this->m<<" y que se empiza a contar desde 0 en lugar de empezar a contar desde 1."<<endl;
            exit(1);  
        }
        else {        
            matrix[((ns)*this->m)+(ms)] = value;
        }    
    }
    template <typename T>
    T Matrix<T>::getValue(int ng, int mg) const{//de forma analoga se hace la funcion para obtener el valor de una posicion especifica en lugar de s se usa g de "get"
        if (ng>=this->n || mg>=this->m){
            cout<<"La ubicacion ingresada en el getValue no es valida, por favor tenga en cueta que la matriz es de dimenciones n="<<this->n<<" y m="<<this->m<<" y que se empiza a contar desde 0 en lugar de empezar a contar desde 1."<<endl; 
            exit(1);
        }
        else {
            return matrix[(ng*this->m) + mg];
        }    
    }
    template <typename T>
    int Matrix<T>::GetDimN() const{//Metodo para conseguir la dimension n de la matriz sin que sea posible cambiar lo. 
        return n;
    }
    template <typename T>
    int Matrix<T>::GetDimM() const{//Metodo para conseguir la dimension m de la matriz sin que sea posible cambiar lo.
        return m;
    }    
    template <typename T>//el destructor encargado de liberar la memoria almacenada em matrix
    Matrix<T>::~Matrix() {
        delete[] matrix;
    }
//Aqui empieza el main.



int main() {

    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Aqui en el main se dejara comentado a modo de minipresentacion, metodos y operadores definidos para las matrices, con el animo de mostrar que funcionan para matrices de cualquier combinacion de n (filas) y m (columnas) van a haber cuatro secciones con ejemplos particulares, la primera consta de matrices con n<m, la segunda tiene matrices con n=m, la tercera es de n>m y la ultima tendra la intencion de mostrar que pasa cuando se trata de operar matrices con distintas dimensiones."<<endl<<"Se deja inicialmente comentado con la intencion de que no se ejecute ese monton de linea, si quiere verlas, esta en liberta de descomentar las."<<endl;

    
    

/*



    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"SECCION (n<m):"<<endl;
    Matrix<int> A(3,4);
    cout<<"Empezamos definiendo una matriz llamada 'A' de dimenciones n=3 y m=4 . La sintaxis para crear la es :'Matrix<int> A(3,4)' y queda de la siguiente manera: "<<endl;
    A.print();
    cout<<endl;
    cout<<"Como podemos ver la matriz esta llena de ceros, puesto es la forma por defecto en la que se inicializa las matrices. Vamos a llenar la matriz con valores arbitrarios para posteriormente mostrar mas operaciones."<<endl;
    A.setValue(2,0,7);
    A.setValue(0,2,4);
    A.setValue(1,3,1);
    A.setValue(1,1,2);
    A.print();
    cout<<endl;
    cout<<"Hasta ahora he estado desplegando la matriz con el metodo 'print()'. Me permito mencionar que tambien defini un metodo llamado 'printTranpose()' el cual muestra como es la transpuesta de la matriz. Pero ojo, solo la muestra en pantalla mas no la crea ni almacena en ningun lugar. La transpuesta de la matriz 'A' es:"<<endl;
    A.printTranspose();
    cout<<endl;
    cout<<"En el ejemplo anterior solo mostramos la matriz pero no la guradamos en ningun lugar, en el caso que quiera crear una matriz 'B' que sea la transpuesta de 'A', usamos la misma sintaxis que con 'A' pero en lugar de dar n y m como argumentos simplemente ponemos la matriz de la que queremos conseguir la transpuesta. Otra opcion es simplemente escribir:'auto B(A)'. Ahora solo basta con usar 'B.print()' y obtenemos"<<endl;
    Matrix<int> Z(A);//La razon por la que uso este Z es por que no pude definir el metodo para que una matriz se transponga a si misma.
    Z.print();
    cout<<endl;
    cout<<"A continuacion voy a realizar ciertos cambios en 'B' para posteriormente operar la con 'A'. La matriz 'B' queda asi:"<<endl;
    Z.setValue(0,0,1);
    Z.setValue(1,1,3);
    Z.setValue(2,0,1);
    Matrix<int> B(Z);
    B.print();
    cout<<endl;
    cout<<"Sea C igual a A+B."<<endl;
    auto C = A+B;
    cout<<"A:"<<endl;
    A.print();
    cout<<"B:"<<endl;
    B.print();
    cout<<"C:"<<endl;
    C.print();
    cout<<"Con la resta es lo mismo solo que evidentemente cambiando '+' por '-'."<<endl;
    cout<<"A continuacion voy a mostrar el operador '+=' entre 'A' y 'B' y como quedan cada una despues del operador;"<<endl;
    cout<<"A:"<<endl;
    A.print();
    cout<<"B:"<<endl;
    B.print();
    cout<<"A+=B"<<endl;
    A+=B;
    cout<<"A:"<<endl;
    A.print();
    cout<<"B:"<<endl;
    B.print();
    cout<<"La operacion de '-=' es analoga"<<endl;
    A-=B;
    cout<<"Para finalizar voy a mostrar la operacion '='"<<endl;
    cout<<"A:"<<endl;
    A.print();
    cout<<"B:"<<endl;
    B.print();
    cout<<"A=B"<<endl;
    A=B;
    cout<<"A:"<<endl;
    A.print();
    cout<<"B:"<<endl;
    B.print();
*/

/*
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"SECCION (n=m):"<<endl;
    Matrix<int> D(4,4);
    cout<<"Empezamos definiendo una matriz llamada 'A' de dimenciones n=3 y m=4 . La sintaxis para crear la es :'Matrix<int> A(4,4)'"<<endl;
    cout<<" Vamos a llenar la matriz con valores arbitrarios para posteriormente mostrar mas operaciones."<<endl;
    D.setValue(2,0,7);
    D.setValue(0,2,4);
    D.setValue(1,3,1);
    D.setValue(1,1,2);
    D.print();
    cout<<endl;
    cout<<"Hasta ahora he estado desplegando la matriz con el metodo 'print()'. Me permito mencionar que tambien defini un metodo llamado 'printTranpose()' el cual muestra como es la transpuesta de la matriz. Pero ojo, solo la muestra en pantalla mas no la crea ni almacena en ningun lugar. La transpuesta de la matriz 'A' es:"<<endl;
    D.printTranspose();
    cout<<endl;
    cout<<"En el ejemplo anterior solo mostramos la matriz pero no la guradamos en ningun lugar, en el caso que quiera crear una matriz 'B' que sea la transpuesta de 'A', usamos la misma sintaxis que con 'A' pero en lugar de dar n y m como argumentos simplemente ponemos la matriz de la que queremos conseguir la transpuesta. Otra opcion es simplemente escribir:'auto B(A)'. Ahora solo basta con usar 'B.print()' y obtenemos"<<endl;
    Matrix<int> Y(D);//La razon por la que uso este Z es por que no pude definir el metodo para que una matriz se transponga a si misma.
    Y.print();
    cout<<endl;
    cout<<"A continuacion voy a realizar ciertos cambios en 'B' para posteriormente operar la con 'A'. La matriz 'B' queda asi:"<<endl;
    Y.setValue(0,0,1);
    Y.setValue(1,1,3);
    Y.setValue(2,0,1);
    Matrix<int> E(Y);
    E.print();
    cout<<endl;
    cout<<"Sea C igual a A+B."<<endl;
    auto F = D+E;
    cout<<"A:"<<endl;
    D.print();
    cout<<"B:"<<endl;
    E.print();
    cout<<"C:"<<endl;
    F.print();
    cout<<"Con la resta es lo mismo solo que evidentemente cambiando '+' por '-'."<<endl;
    cout<<"A continuacion voy a mostrar el operador '+=' entre 'A' y 'B' y como quedan cada una despues del operador;"<<endl;
    cout<<"A:"<<endl;
    D.print();
    cout<<"B:"<<endl;
    E.print();
    cout<<"A+=B"<<endl;
    D+=E;
    cout<<"A:"<<endl;
    D.print();
    cout<<"B:"<<endl;
    E.print();
    cout<<"La operacion de '-=' es analoga"<<endl;
    D-=E;
    cout<<"Para finalizar voy a mostrar la operacion '='"<<endl;
    cout<<"A:"<<endl;
    D.print();
    cout<<"B:"<<endl;
    E.print();
    cout<<"A=B"<<endl;
    D=E;
    cout<<"A:"<<endl;
    D.print();
    cout<<"B:"<<endl;
    E.print();
*/

/*
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"SECCION (n>m):"<<endl;
    Matrix<int> G(4,5);
    cout<<"Empezamos definiendo una matriz llamada 'A' de dimenciones n=3 y m=4 . La sintaxis para crear la es :'Matrix<int> A(4,5)'"<<endl;
    cout<<"Vamos a llenar la matriz con valores arbitrarios para posteriormente mostrar mas operaciones."<<endl;
    G.setValue(2,0,7);
    G.setValue(0,2,4);
    G.setValue(1,3,1);
    G.setValue(1,1,2);
    G.print();
    cout<<endl;
    cout<<"Hasta ahora he estado desplegando la matriz con el metodo 'print()'. Me permito mencionar que tambien defini un metodo llamado 'printTranpose()' el cual muestra como es la transpuesta de la matriz. Pero ojo, solo la muestra en pantalla mas no la crea ni almacena en ningun lugar. La transpuesta de la matriz 'A' es:"<<endl;
    G.printTranspose();
    cout<<endl;
    cout<<"En el ejemplo anterior solo mostramos la matriz pero no la guradamos en ningun lugar, en el caso que quiera crear una matriz 'B' que sea la transpuesta de 'A', usamos la misma sintaxis que con 'A' pero en lugar de dar n y m como argumentos simplemente ponemos la matriz de la que queremos conseguir la transpuesta. Otra opcion es simplemente escribir:'auto B(A)'. Ahora solo basta con usar 'B.print()' y obtenemos"<<endl;
    Matrix<int> X(G);//La razon por la que uso este Z es por que no pude definir el metodo para que una matriz se transponga a si misma.
    X.print();
    cout<<endl;
    cout<<"A continuacion voy a realizar ciertos cambios en 'B' para posteriormente operar la con 'A'. La matriz 'B' queda asi:"<<endl;
    X.setValue(0,0,1);
    X.setValue(1,1,3);
    X.setValue(2,0,1);
    Matrix<int> H(X);
    H.print();
    cout<<endl;
    cout<<"Sea C igual a A+B."<<endl;
    auto I = G+H;
    cout<<"A:"<<endl;
    G.print();
    cout<<"B:"<<endl;
    H.print();
    cout<<"C:"<<endl;
    I.print();
    cout<<"Con la resta es lo mismo solo que evidentemente cambiando '+' por '-'."<<endl;
    cout<<"A continuacion voy a mostrar el operador '+=' entre 'A' y 'B' y como quedan cada una despues del operador;"<<endl;
    cout<<"A:"<<endl;
    G.print();
    cout<<"B:"<<endl;
    H.print();
    cout<<"A+=B"<<endl;
    G+=H;
    cout<<"A:"<<endl;
    G.print();
    cout<<"B:"<<endl;
    H.print();
    cout<<"La operacion de '-=' es analoga"<<endl;
    G-=H;
    cout<<"Para finalizar voy a mostrar la operacion '='"<<endl;
    cout<<"A:"<<endl;
    G.print();
    cout<<"B:"<<endl;
    H.print();
    cout<<"A=B"<<endl;
    G=H;
    cout<<"A:"<<endl;
    G.print();
    cout<<"B:"<<endl;
    H.print();
*/

/*
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"SECCION errores:"<<endl;
    Matrix<int> M1(2,2);
    Matrix<int> M2(2,3);
    //M1.getValue(2,2);
    //M1.setValue(2,2,5);
    //auto M3=M1+M2;
    //M1=M2;
    
*/
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    return 0;
}
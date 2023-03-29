#include<iostream>

using namespace std;

template <class T> class matrix    // Creamos el template de la clase
{
private:
    T* datos;
    int filas;               // Atributos privados, lista donde se van a
    int colums;              // guardar todas las entradas, # FIILA , # COLUMNAS 

public:  
    // Constructor    
    matrix(int filas , int colums): filas(filas), colums(colums)   
    {
        datos = new T[ filas * colums ];
        for( int i = 0; i < filas * colums ; i++)
        {
            datos[i] =  0;
        }     
    }


    // Copy constructor
    matrix( const matrix& other) : filas(other.filas) , colums(other.colums)
    {
        datos = new T[filas*colums];
        for (int i=0 ; i< filas* colums ; i++)
        {
            datos[i] =  other.datos[i];
        }
    }
    
    // Desrtructor
    ~matrix(){
        delete[]  datos;
    }

    //Para obtener la dimesión de la matriz ( filas * columnas )
    // Para los métodos las entradas de la matriz empiezan en 0,0 ... n,m
    int getDim() const;
    
    // Valor de una entrada de la matriz
    T get( int i, int j) const;

    //Para defenir una entrada de la matriz
    void set(int i ,int j,  T m );


    

    //Para mostrar la matriz en consola
    void print()
    {
        for(int i=0 ; i<colums ; i++)
        {
            for (int j= 0 ; j < filas ; j++)
            {
                cout << datos[i*filas + j]<< " ";
            }
            cout << endl ;
        }
    }

    // Método para la transpuesta
    matrix<T> tr() const
    {
        matrix mtr(colums , filas);
        for(int i=0 ; i<colums ; i++)
        {
            for (int j= 0 ; j < filas ; j++)
            {
                mtr.datos[filas*i + j] = datos[j*filas + i];
            }
        }
        return mtr;
    }

    //Sobrecarga de operadores
    // =
    matrix<T>& operator=( const matrix<T>& m)
    {
        if (this != &m)
        {
            if( filas==m.filas && colums == m.colums)
            {
                delete[] datos;
                filas  = m.filas;
                colums = m.colums;
                datos = new T[filas * colums];
            
            }
            else {
                cout << " Para igualar dos objetos matriz, estos deben ser iguales"<< endl;
                exit(1);
                }
            for(int i=0 ; i<colums ; i++)
            {
                for (int j= 0 ; j < filas ; j++)
                {
                    datos[i*filas + j] = m.datos[i*filas + j];
                }
            }        
        }
        return *this;
    }

    // Operador +
    matrix<T> operator+(const matrix<T>& m) const 
    {
        if( filas==m.filas && colums == m.colums)
        {
            matrix s(filas,colums);
            for ( int i=0; i<filas*colums; i++)
            {
                s.datos[i] = datos[i] + m.datos[i];
            }
            return s;
        }
        else 
        {
            cout << "Para sumar matrices las filas y columnas deben ser iguales" << endl;
            exit(1);
        }    
    }

    // Operador - 
    matrix<T> operator-(const matrix<T>& m) const 
    {
        if( filas==m.filas && colums == m.colums)
        {
            matrix s(filas,colums);
            for ( int i=0; i<filas*colums; i++)
            {
                s.datos[i] = datos[i] - m.datos[i]; 
            }
            return s;
        }
        else 
        {
            cout << "Para sumar matrices las filas y columnas deben ser iguales" << endl;
            exit(1);
        }    
    }

    // Operador +=
    matrix<T>& operator +=(const matrix<T>& m) 
    {
        if( filas==m.filas && colums == m.colums)
        {         
            for ( int i=0; i<filas*colums; i++)
            {
                datos[i] += m.datos[i]; 
            }
        return *this; 
        }
        else 
        {
            cout << "Para usar +=  las filas y columnas deben ser iguales" << endl;
            exit(1);
        } 
        
    }

    // Operador -=
    matrix<T>& operator -=(const matrix<T>& m) 
    {
        if( filas==m.filas && colums == m.colums)
        {         
            for ( int i=0; i<filas*colums; i++)
            {
                datos[i] -= m.datos[i]; 
            }
        return *this; 
        }
        else 
        {
            cout << "Para usar -=  las filas y columnas deben ser iguales" << endl;
            exit(1);
        } 
        
    }

};

// Se especifican los metodos

//Obtener la dimensión de la matriz (filas * columnas)
template<class T> int matrix<T>:: getDim() const 
{ 
    return filas*colums;
}

//Obtener el valor de una entrada especificada
//haceindo verificación de que los valores pedidos estén dentro del los valores establecidos al crear la matriz
template<class T> T matrix<T>::get(int i , int j) const{
    if (i>filas  || i<0 || j<0 || j > filas)
    {
        cout << "El valor ingresado para las filas o las columnas es inválido, está fuera del rango de la matriz" << endl;
        exit(1);
    }
    else {
        return datos[i*filas + j];
        }
    }
    

template<class T> void matrix<T>::set(int i, int j ,T x)
{   
    if (i>filas  || i<0 || j<0 || j > filas)
    {
        cout << "El valor ingresado para las filas o las columnas es inválido, está fuera del rango de la matriz" << endl;
        exit(1);
    }
    else 
    {
        datos[j*filas + i] = x;
    }
}


int main()
{
    cout << endl; 
    cout << "Se crea una matriz m1, se le asigna a todas las entradas '0' por defecto " << endl;
    cout << endl;
    matrix <int> m1(3,3);
    
    cout << "Matriz ,m1:" << endl;
    m1.print();
    cout << " ..............................................." << endl;
    cout << endl;
    cout<< "Le damos valores a cada una de las entradas de las matriz"<< endl;
    cout << endl;

    
    m1.set(0,0,1); 
    m1.set(0,1,2); 
    m1.set(0,2,3); 
    m1.set(1,0,4); 
    m1.set(1,1,5); 
    m1.set(1,2,6); 
    m1.set(2,0,7); 
    m1.set(2,1,8); 
    m1.set(2,2,9); 
    cout << " La matriz m1 con los valores que le asignamos queda así: " << endl;
    cout<< "Matriz m1: " << endl;
    m1.print()  ;
    cout << endl;
    cout << " ..............................................." << endl;
    cout << " Usamos el método (getDim) para obtener la dimensión de la matriz m1" << endl;
    cout << " La dimensión de la matriz 'm1' es: " << m1.getDim() << endl;
    cout << endl; 
    cout << " ..............................................." << endl;
    cout << " Utilicemos el método 'get' para concer el valor de una posición determinada, en este caso el valor de la entrada (2,3)  es : " << endl;
    cout <<  m1.get(1,2) << endl;   // como la lista comienza en 0,0 se utiliza la entrada que queramos -1
    cout << endl; 
    cout << " ..............................................." << endl;
    cout << " También se puede modificar una entrada luego de que la hayamos definido, con la función 'set' " << endl;
    cout << "de igual manera como rellenamos las entradas de la matriz. Cambiemos el valor de la primer entrada de la matriz por 35" << endl;
    cout << endl;
    m1.set(0,0, 35);
    m1.print()  ;
    cout << endl;

    

    cout << " ..............................................." << endl;

    cout << endl;
    cout << "Veamos el método para encontrar la transpuesta de la matriz" << endl;
    cout << "pdta: Para msotrar esta matriz usamos la sobrecarga del operador '='" << endl;
    cout << endl; 

    matrix <int> mtrans(3,3);   // Se crea uan matriz vacia 3*3 ( a la que se le asignará la inversa de 'A')
    //matrix<int> mtrans (4,3);  // Para mostrar la condicion de que al igualar dos matrices de != dim da error

    
    mtrans = m1.tr();   

    cout << endl;
    cout << " La matriz m1 original: " << endl;
    cout << endl; 
    m1. print();
    cout << endl;
    cout << " La matriz m1 transpuesta: " << endl;
    cout << endl;
    mtrans.print();


    cout << " ..............................................." << endl;

    cout << endl;
    cout << "Operador '+'"<< endl;
    cout << " Vamos a sumar la matriz m1 y m2 " << endl;
    cout << endl ;
    cout << " m1: "<< endl;
    cout << endl; 
    m1.print();
    cout << endl; 

    matrix <int> m2(3,3);
    m2.set(0,0,4); 
    m2.set(0,1,5); 
    m2.set(0,2,3); 
    m2.set(1,0,6); 
    m2.set(1,1,7); 
    m2.set(1,2,8); 
    m2.set(2,0,6); 
    m2.set(2,1,4); 
    m2.set(2,2,3); 

    cout << " m2: " << endl;
    cout << endl;
    m2.print();

    cout << endl;
    cout << " m1 + m2 = " << endl ; 
    cout << endl; 

    auto sum = m1 + m2 ; 

    sum.print();
    cout << endl;

    cout << " ..............................................." << endl;

    cout << endl;
    cout << "Operador '-'"<< endl;
    cout << " Vamos a restar la matriz m1 y m2 " << endl;
    cout << endl ;
    cout << " m1: "<< endl;
    cout << endl; 
    m1.print();
    cout << endl; 
    cout << " m2: " << endl;
    cout << endl;
    m2.print();
    cout << endl;
    cout << " m1 - m2 = " << endl ; 
    cout << endl;
    auto res = m1 - m2; 
    res.print();

    cout << " ..............................................." << endl;

    cout << endl;
    cout << " Operador '+='"<< endl;
    cout << " Vamos a realizar la operación m1 += m2 " << endl;
    cout << " Lo que nos va a asignar a la matriz m1 los valores de la operación m1+m2: " << endl;
    cout << endl ;
    
    m1 += m2;
    
    m1.print();

    cout << " ..............................................." << endl;

    cout << endl;
    cout << " Operador '-='"<< endl;
    cout << " Vamos a realizar la operación m2 -= m1 " << endl;
    cout << " Lo que nos va a asignar a la matriz m2 los valores de la operación m2-m1: " << endl;
    cout << endl ;
    
    m2 -= m1;
    
    m2.print();

    cout << " ..............................................." << endl;

    cout << endl;
    cout << " Además se tiene para la sobre carga de operadores y los métodos "<< endl;
    cout << " condiciones en las que se imprime un mensaje si el usario quiere " << endl;
    cout << " realizar operaciones que no están permitidas." << endl;

    cout << " ..............................................." << endl;
    cout << endl;

    return 0;
}





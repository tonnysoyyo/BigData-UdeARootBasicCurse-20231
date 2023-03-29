#include <iostream>
#include <vector>

using namespace std;

template<typename T> 
class Matriz {
private:
	int filas; // Número de filas
	int columnas; // Número de columnas
	T* datos; // Puntero al arreglo dinámico que almacena los elementos de la matriz

public:
	Matriz(int filas, int columnas);
	~Matriz(); 
	Matriz(const Matriz& otra);
	void set(int fila, int columna, T valor);
	T get(int fila, int columna) const;
	void print();
	Matriz<T> transpuesta() const;
	
	Matriz<T> operator+(const Matriz<T>& otra) const;
	Matriz<T> operator-(const Matriz<T>& otra) const;
	Matriz<T>& operator=(const Matriz<T>& otra);
	Matriz<T>& operator+=(const Matriz<T>& otra);
	Matriz<T>& operator-=(const Matriz<T>& otra);
	};

// Constructor que recibe el número de filas y columnas y crea el arreglo dinámico:
template<typename T>
Matriz<T>::Matriz(int filas, int columnas) : filas(filas), columnas(columnas) {
	datos = new T[filas * columnas];
	}

// Destructor que libera la memoria del arreglo dinámico:
template<typename T>
Matriz<T>::~Matriz() {
	delete[] datos; 
	}

// Constructor de copia
template<typename T>
Matriz<T>::Matriz(const Matriz& otra) : datos(new T[otra.filas * otra.columnas]), filas(otra.filas), columnas(otra.columnas) {
	for (int i = 0; i < filas * columnas; i++) {
		datos[i] = otra.datos[i];
		}
	}

// Método para poner los valores a la matriz:
template<typename T>
void Matriz<T>::set(int fila, int columna, T valor) {
	datos[fila * columnas + columna] = valor;
	}

// Método para obtener los valores de la matriz:
template<typename T>
T Matriz<T>::get(int fila, int columna) const {
	if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) { // Verifica que los índices estén dentro del rango válido para evitar violación de segmento
		throw out_of_range("Índices de matriz fuera de rango");
		}
	
	return datos[fila * columnas + columna];
	}

// Método para imprimir la matriz:
template<typename T>
void Matriz<T>::print() {
	for (int i = 0; i < filas; i++) {
		cout << "| ";
		for (int j = 0; j < columnas; j++) {
			cout << get(i, j) << " ";
			}
		cout << "|" << endl;
		}
	cout << endl;
	}

// Método para calcular la transpuesta:
template<typename T>
Matriz<T> Matriz<T>::transpuesta() const {
	Matriz<T> transpuesta(columnas, filas); // Crear una nueva matriz con las dimensiones invertidas
	
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			transpuesta.set(j, i, get(i, j));
			}
		}
	
	return transpuesta;
	}

// Sobrecarga de operadores:

template<typename T>
Matriz<T> Matriz<T>::operator+(const Matriz<T>& otra) const {
	if (filas != otra.filas || columnas != otra.columnas) {
		throw invalid_argument("Las matrices deben tener las mismas dimensiones"); // Verifica que ambas matrices tengan las mismas dimensiones
		}
	
	Matriz<T> resultado(filas, columnas);
	
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			resultado.set(i, j, get(i, j) + otra.get(i, j));
			}
		}
	
	return resultado;
	}

template<typename T>
Matriz<T> Matriz<T>::operator-(const Matriz<T>& otra) const {
	if (filas != otra.filas || columnas != otra.columnas) {
		throw invalid_argument("Las matrices deben tener las mismas dimensiones"); // Verifica que ambas matrices tengan las mismas dimensiones
        }
        
    Matriz<T> resultado(filas, columnas);
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado.set(i, j, get(i, j) - otra.get(i, j));
			}
		}
		
    return resultado;
	}

template<typename T>
Matriz<T>& Matriz<T>::operator=(const Matriz<T>& otra) {
	if (this != &otra) { // Verifica que no se esté copiando la misma matriz
		delete[] datos; // Libera la memoria del arreglo dinámico actual
		
		// Reserva nueva memoria:
		filas = otra.filas;
		columnas = otra.columnas;
		datos = new T[otra.filas * otra.columnas];
		
		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				set(i, j, otra.get(i, j));
				}
			}
		}
	
	return *this;
	}

template<typename T>
Matriz<T>& Matriz<T>::operator+=(const Matriz<T>& otra) {
	if (filas != otra.filas || columnas != otra.columnas) {
		throw invalid_argument("Las matrices deben tener las mismas dimensiones"); // Verifica que ambas matrices tengan las mismas dimensiones
		}
	
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			set(i, j, get(i, j) + otra.get(i, j));
			}
		}
	
	return *this;
	}

template<typename T>
Matriz<T>& Matriz<T>::operator-=(const Matriz<T>& otra) {
	if (filas != otra.filas || columnas != otra.columnas) {
		throw invalid_argument("Las matrices deben tener las mismas dimensiones"); // Verifica que ambas matrices tengan las mismas dimensiones
		}
	
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			set(i, j, get(i, j) - otra.get(i, j));
			}
		}
	
	return *this;
	}

//leer datos de un archivo
#include <iostream>
#include <fstream> // flujo de archivo
#include <cstdlib>
#include <iomanip>

using namespace std;

void imprimirLinea( int, const string, double ); // prototipo

int main()
{
  
  //ifstream archivoClientesEntrada( "../clientes.dat", ios::in );
  ifstream archivoClientesEntrada( "clientes.dat" );

  if( !archivoClientesEntrada )
  //if( archivoClientesEntrada.fail() )   
    {
      //cout << "No se pudo abrir el archivo" << endl;
      cerr << "Error: no se pudo abrir el archivo" << endl;
      exit( 1 );
    }

  int cuenta;
  char nombre[ 30 ];
  double saldo;
  cout << left << setw( 10 ) << "Cuenta" << setw( 13 )
       << "Nombre" << "Saldo" << endl << fixed << showpoint;

  
  // muestra cada registro en el archivo
   
  while ( archivoClientesEntrada >> cuenta >> nombre >> saldo ){
    imprimirLinea( cuenta, nombre, saldo );
  }
  
  //
  /*
  archivoClientesEntrada >> cuenta >> nombre >> saldo;
  while(archivoClientesEntrada.good()) // comprueba el siguiente carácter
    {
      imprimirLinea( cuenta, nombre, saldo );
      archivoClientesEntrada >> cuenta >> nombre >> saldo;
    }
  */
  //
  /*
  string linea;
  while (getline(archivoClientesEntrada,linea))
    {
      cout << linea << endl;
    }
  */
  return 0; 
}

// muestra una sola linea del archivo
void imprimirLinea( int cuenta, const string nombre, double saldo )
{
cout << left << setw( 10 ) << cuenta << setw( 13 ) << nombre
<< setw( 7 ) << setprecision( 2 ) << right << saldo << endl;
}

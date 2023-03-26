#include <iostream>
#include <cmath>

using namespace std;
double integral(double (*fun)(double), double a, double b, int n)
{
    double x_i = (b-a)/n;
    double sum = 0;
    for (double i = a; i<b; i+=x_i)
    {
        sum+=fun(i);
    }
    return sum*x_i;
}
/*
Con double (*fun)(double) como primer argumento de la función le estoy diciendo que voy a 
recibir como primer parámetro el puntero de una función, esto es el (*fun), el double que
está antes se refiere a que vamos a recibir un double como salida, y el double de después
es que el argumento que recibe la función *fun recibe un double como argumento.
*/
int main()
{
    cout << integral(sin,0,2*M_PI,1000)<< endl;
    return 0;
}
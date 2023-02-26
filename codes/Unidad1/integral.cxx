#include<iostream>
#include<cmath>  // sin, M_PI
using namespace std;

double funcion(double x)
{   
 //return x*x..... // la función que quiero integrar
    return sin(x);
}


double integral(double a, double b, int n)
{
    double delta=(b-a)/n;
    double sum=0;
    for(double x_i=a;  x_i<b;   x_i=x_i+delta)
    {
        sum+=funcion(x_i);
    }
    return sum*delta;
}


int main()
{

    double a=0, b=2*M_PI; // intervalo
    
    double res = integral(a,b,100);
    cout<<"La integral entre (0,2pi) de sin = "<<res<<endl;
    return 0; 

}

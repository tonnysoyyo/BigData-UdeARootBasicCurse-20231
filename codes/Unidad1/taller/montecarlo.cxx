#include <random>
#include <iostream>

using namespace std;

class Integral
{
    protected:
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen; // seed the generator
    double (*fun)(double);
    double a,b;
    uniform_real_distribution<double> unif;
    public:
        Integral(double (*_fun)(double),double min, double max):fun(_fun),gen(rd()),unif(min,max),a(min),b(max){
        }

        virtual double integrar(int n){ // n es la cantidad de nuúmeros aleatorios 
            //https://es.wikipedia.org/wiki/Integraci%C3%B3n_de_Monte_Carlo#Algoritmo
            double Ef=0;
            for(int i=0;i<n;i++)
            {
              Ef+=fun(unif(gen));  
            }
            return ((b-a)/n)*Ef;
        }
};

int main()
{
    Integral inte(sin,0,2*M_PI);
    cout<<inte.integrar(100000)<<endl;
    return 0;
}

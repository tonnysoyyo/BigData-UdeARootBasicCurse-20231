#include<iostream>
using namespace std;
void incremento_ptr(int *p)
{
    (*p)++;
}
void incremento_ref(int &n)
{
    n++; //como es referencia no necesito la sintaxis de aritmética de punteros
}
int main()
{
    int num;
    //int *p = new int;
    int *p;
    p = new int;
    (*p) = 321;
    cout<<"dirreccón de memeria = "<<p<<endl;
    cout<<"valor = "<<*p<<endl;
    
    incremento_ptr(p);
    cout<<"valor (p) = "<<*p<<endl;
    delete p;
    p=nullptr;
    cout<<"dirreccón de memeria (p) = "<<p<<endl;

    p = &num; // asi se le asigna un valor a p, el operador & retorna la posición de memoria de num
    num = 1;

    cout<<"dirreccón de memeria (p) = "<<p<<endl;
    cout<<"dirreccón de memeria (num) = "<<&num<<endl;
    cout<<"valor (p) = "<<*p<<endl;
    cout<<"valor (num) = "<<num<<endl;
    
    incremento_ref(num);
    cout<<"valor (p) = "<<*p<<endl;
    cout<<"valor (num) = "<<num<<endl;
    return 0;
}
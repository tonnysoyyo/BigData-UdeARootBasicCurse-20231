#include<Particle.h>

int main()
{
    double pos1[]={0,0};
    double pos2[]={1,1};
    Particle p1(2,pos1);
    Particle p2(2,pos2);
    p1.print();
    p2.print();
    cout<<"la distancia entre p1 y p2 es "<<p1.distance(p2)<<endl;
    //OJO A ESTO
    //p1=p2; // aún no sobrecargamos operadores, comportamiento indefinido o error de compilación
    //p1.print();
    //p2.print();

    auto pp1=new Particle(2,pos1);
    auto pp2=new Particle(2,pos2);
    pp1->print(); //nótese que cuando es puntero los métodos se llaman con el operador ->
    pp2->print();
    cout<<"la distancia entre pp1 y pp2 es "<<pp1->distance(*pp2)<<endl; //podemos pasar el valor del puntero por que tenemos copy contructor, si lo comentamos no funciona
    cout<<"la distancia entre pp1 y pp2 es "<<pp1->distance(pp2)<<endl; //este lo podemos usar, pasando el puntero directamente por que tenemos sobrecargado el método distance (polimosfismo)

    //Este caso ya lo estudiamos
    pp1=pp2; // ¿qué pasa aquí?
    pp2->print();

    Particle p3(p2); //copy constructor
    p3.print();
    p2.print();
    delete pp1;
    //delete pp2; //arriba asigne pp2 a pp1, no se puede hacer una libraciṕn doble 
    return 0;
}
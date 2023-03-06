#include<iostream>
#include<cmath>

using namespace std;

class Particle {
private:
    double *position;
    int dim;
protected:
    void copy(double *posI, double *posO, int dim){ //se podría usar  std::memcpy
        for(int i=0; i<dim; i++){
            posO[i] = posI[i];
        }
    }    
public:
    Particle(int dim, double *position) {
        this->dim = dim;
        this->position = new double[dim];
        copy(position,this->position,dim);
    }

    Particle(const Particle &p){
       dim = p.dim;
       position=new double[dim];
       copy(p.position, position,dim);
    }

    ~Particle(){
        delete[] position;
    }
    
    void print(){
        for(int i=0;i<dim;i++){
        cout<<position[i]<<" ";
        }
        cout<<endl;
    }

    int getDim(){
        return dim;
    }

    double getPosition(int i){
        if(i>dim)
        {
            cout<<"ERROR: se trata de acceder a una posición mayor que la dimensión"<<endl;
            exit(1); //salida de error
        }
        return position[i];
    }
    void setPosition(int i, double value){
        if(i>dim)
        {
            cout<<"ERROR: se trata de acceder a una posición mayor que la dimensión"<<endl;
            exit(1); //salida de error
        }
        position[i]=value;
    }

    double distance(Particle p)
    {
        if(dim != p.getDim())
        {
            cout<<"ERROR:no se puede calcular la distancia entre dos partículas de diferente dimensión"<<endl;
            exit(1); //salida de error
        }
        double sum = 0;
        for(int i=0;i<dim;i++)
        {
            sum+=(position[i]+p.getPosition(i))*(position[i]+p.getPosition(i));
        }
        return sqrt(sum);
    }

    double distance(Particle *p) //polimorfismo, métodos que se llaman igual, pero reciben argumentos diferentes
    {
        if(dim != p->getDim())
        {
            cout<<"ERROR:no se puede calcular la distancia entre dos partículas de diferente dimensión"<<endl;
            exit(1); //salida de error
        }
        double sum = 0;
        for(int i=0;i<dim;i++)
        {
            sum+=(position[i]+p->getPosition(i))*(position[i]+p->getPosition(i));
        }
        return sqrt(sum);        
    }

};

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
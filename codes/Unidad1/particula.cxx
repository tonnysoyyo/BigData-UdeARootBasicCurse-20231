#include<iostream>
#include<cmath>

using namespace std;

class Particle {
private:
    double *position;
    int dim;
protected:
    void copy(double *posI, double *posO, int dim){
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

    Particle(int dim){
       this->dim = dim;
       position=new double[dim];
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

};

int main()
{
    double pos1[]={0,0};
    double pos2[]={1,1};
    Particle p1(2,pos1);
    Particle p2(2,pos2);
    p1.print();
    p2.print();
    cout<<"la distancia entre p1 y p2 es "<<p1.distance(p2);
    return 0;
}
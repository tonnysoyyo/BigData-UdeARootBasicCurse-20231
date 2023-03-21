#include<Particle.h>

void Particle::copy(double *posI, double *posO, int dim){ 
        for(int i=0; i<dim; i++){
            posO[i] = posI[i];
        }
    }    

Particle::Particle(int dim, double *position) {
    this->dim = dim;
    this->position = new double[dim];
    copy(position,this->position,dim);
}

Particle::Particle(const Particle &p){
    dim = p.dim;
    position=new double[dim];
    copy(p.position, position,dim);
}

Particle::~Particle(){
    delete[] position;
}
    
void Particle::print(){
    for(int i=0;i<dim;i++){
    cout<<position[i]<<" ";
    }
    cout<<endl;
}

int Particle::getDim(){
    return dim;
}

double Particle::getPosition(int i){
    if(i>dim)
    {
        cout<<"ERROR: se trata de acceder a una posición mayor que la dimensión"<<endl;
        exit(1); //salida de error
    }
    return position[i];
}
void Particle::setPosition(int i, double value){
    if(i>dim)
    {
        cout<<"ERROR: se trata de acceder a una posición mayor que la dimensión"<<endl;
        exit(1); //salida de error
    }
    position[i]=value;
}

double Particle::distance(Particle p)
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

double Particle::distance(Particle *p) //polimorfismo, métodos que se llaman igual pero reciben argumentos diferentes
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

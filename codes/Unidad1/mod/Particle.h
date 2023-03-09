#ifndef PARTICLE_H
#define PARTICLE_H

#include<iostream>
#include<cmath>

using namespace std;

class Particle {
private:
    double *position;
    int dim;
protected:
    void copy(double *posI, double *posO, int dim);
public:
    Particle(int dim, double *position);

    Particle(const Particle &p);

    ~Particle();
    
    void print();

    int getDim();

    double getPosition(int i);

    void setPosition(int i, double value);

    double distance(Particle p);
    double distance(Particle *p); //polimorfismo, métodos que se llaman igual pero reciben argumentos diferentes

};
#endif
#ifndef STAR_H
#define STAR_H
#include<Particle.h>

class Star:public Particle
{

    private:
        double mass;
        string name;
        double temp;

    public:
        Star(double pisition[3], double mass,  double temp, string name):Particle(3,pisition)
        {
            this->mass = mass;
            this->name = name; 
        }

        double getMass(){
            return mass;
        }
        string getName(){
            return name;
        }
        double getTemp(){
            return temp;
        }
};

#endif
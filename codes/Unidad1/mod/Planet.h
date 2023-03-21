#ifndef PLANET_H
#define PLANET_H
#include<Particle.h>

class Planet:public Particle
{

    private:
        double mass;
    public:
        Planet(double pos[3], double mass):Particle(3,pos)
        {
            this->mass = mass;
        }
    
        virtual int numSatellites() = 0;

        virtual bool hasStmosphere() = 0;

};


class Mars:public Planet
{
    public:
        Mars(double pos[3]):Planet(pos,6.4185*10e23)
        {

        }

        int numSatellites()
        {
            return 2;
        }

        virtual bool hasStmosphere()
        {
            return false;
        }

};


class Earth:public Planet
{
    public:
        Earth(double pos[3]):Planet(pos,6.4185*10e23)
        {

        }

        int numSatellites()
        {
            return 1;
        }

        bool hasStmosphere()
        {
            return true;
        }

};

#endif
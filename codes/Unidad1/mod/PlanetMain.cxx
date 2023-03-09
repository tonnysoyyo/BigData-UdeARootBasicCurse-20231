#include<Planet.h>

int main()
{
    double pos[]={1,1,1};
    //Planet  p(pos,0); esto no se puede por que la clase es virtual pura
    Earth e(pos);
    cout<<"num lunas = "<<e.numSatellites()<<endl;
    return 0;
}
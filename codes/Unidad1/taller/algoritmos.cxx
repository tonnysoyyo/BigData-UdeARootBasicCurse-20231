#include<iostream>
#include<vectort.h>

template<class T> class Algoritmos
{
    private:
    Vector<T> &v;
    int menor(int j)
    {
        T m=v[0];
        int pos = 0;
        for(int i=j;i<v.getSize();i++){
            if(v[i]<m){
                m=v[i];
                pos=i;
            }
        }
        return pos;

    }
    public:
    Algoritmos(Vector<T> &_v):v(_v){
    }

    T max(){
        T m=v[0];
        for(int i=0;i<v.getSize();i++){
            if(v[i]>m) m=v[i];
        }
        return m;
    }

    T min(){
        T m=v[0];
        for(int i=0;i<v.getSize();i++){
            if(v[i]<m) m=v[i];
        }
        return m;
    }

    Vector<T> ordenar()
    {
        Vector<T> nv(v);

        for( int i = 0; i < nv.getSize(); i++ ){
            for( int j = 1; j < nv.getSize() - i; j++ ){
                // Intercambiamos
                if( nv[j] < nv[j-1] ){
                    T temp = nv[j];
                    nv[j] = nv[j-1];
                    nv[j-1] = temp;
                }
            }
        }
        return nv;
    }

};

int main(){
    Vector<int> v1(5);
    v1.set(0,1);
    v1.set(1,-2);
    v1.set(2,5);
    v1.set(3,38);
    v1.set(4,3);
    Algoritmos<int> algo(v1);

    cout<<"min = "<<algo.min()<<endl;
    cout<<"max = "<<algo.max()<<endl;
    auto v2= algo.ordenar();
    v2.print();
}
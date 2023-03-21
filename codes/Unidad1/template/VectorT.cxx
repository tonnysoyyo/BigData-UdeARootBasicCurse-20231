#include <cmath>
#include <iostream>

using namespace std;

template<class T> class Vector {
private:
    T* data;
    int size;

public:
    Vector(int n) : size(n) {
        data = new T[n];
        for (int i = 0; i < size; i++) {
            data[i] = 0.0;
        }
    }

    Vector(const Vector& v) : size(v.size) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = v.data[i];
        }
    }

    ~Vector() {
        delete[] data;
    }

    int getSize() const ;
    // int getSize() const {
    //     return size;
    // }

     T get(int i) const;
    // T get(int i) const {
    //     return data[i];
    // }

    void set(int i, T x);
    // void set(int i, T x) {
    //     data[i] = x;
    // }

    Vector<T>& operator=(const Vector<T>& v) {
        if (this != &v) {
            if (size != v.size) {
                delete[] data;
                size = v.size;
                data = new T[size];
            }
            for (int i = 0; i < size; i++) {
                data[i] = v.data[i];
            }
        }
        return *this;
    }

    Vector<T> operator+(const Vector<T>& v) const {
        Vector w(size);
        for (int i = 0; i < size; i++) {
            w.data[i] = data[i] + v.data[i];
        }
        return w;
    }

    Vector<T> operator-(const Vector<T>& v) const {
        Vector w(size);
        for (int i = 0; i < size; i++) {
            w.data[i] = data[i] - v.data[i];
        }
        return w;
    }
    T& operator[](int index)
    {
        return data[index];
    }

};


template<class T>  int Vector<T>::getSize() const {
        return size;
    }

template<class T>  T Vector<T>::get(int i) const {
        return data[i];
    }

template<class T> void Vector<T>::set(int i, T x) {
        data[i] = x;
    }




int main()
{

    Vector<int> v1(2);
    Vector<int> v2(2);
    v1.set(0,2);
    v1.set(1,2);
    
    v2.set(0,1);
    v2.set(1,1);

    auto v3=v1+v2;
    cout<<v3.get(0)<<"  "<<v3.get(1)<<endl;
    v3=v1-v2;
    cout<<v3.get(0)<<"  "<<v3.get(1)<<endl;
    v3=v2;
    cout<<v3.get(0)<<"  "<<v3.get(1)<<endl;

    //esto es posible después de sobrecargar []
    cout<<v3[0]<<"  "<<v3[1]<<endl;
    v3[0]=-1; // lvalue required as left operand of assignment (poner & en la variable de retorno)
    cout<<v3[0]<<"  "<<v3[1]<<endl;
    return 0;
}
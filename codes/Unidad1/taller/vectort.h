#include<iostream>

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
    void print(){
        for(int i=0;i<size;i++){
        cout<<data[i]<<" ";
        }
        cout<<endl;
    }
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


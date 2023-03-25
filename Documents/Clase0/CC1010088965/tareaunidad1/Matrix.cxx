#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

template<class T> class Matriz {
private:
    T* data;
    int size_rows;
    int size_columns;

public:
    Matriz(int n, int m) : size_rows(n), size_columns(m) {
        if (n <= 0 || m <= 0) {
            throw std::invalid_argument("Number of rows and columns must be above zero");
        }
        data = new T[n*m];
        for (int i = 0; i < size_rows*size_columns; i++) {
            data[i] = 0.0;
        }
    }

    ~Matriz() {
        delete[] data;
    }

    T get(int i, int j) const {
        return data[i*size_columns + j];
    }

    void set(int i, int j, T val) {
        data[i*size_columns + j] = val;
    }

    Matriz<T>& operator=(const Matriz<T>& m) {
        if (this != &m) {
            if (size_columns != m.size_columns || size_rows != m.size_rows) {
                delete[] data;
                size_rows = m.size_rows;
                size_columns = m.size_columns;
                data = new T[size_rows*size_columns];
            }
            for (int i = 0; i < size_columns*size_rows; i++) {
                data[i] = m.data[i];
            }
        }
        return *this;
    }

    Matriz<T> operator+(const Matriz<T>& m) const {
        if (m.size_rows != size_rows || m.size_columns != size_columns) {
            throw std::invalid_argument(
                "Number of rows and columns must be the same in matrices being summed"
            );
        }
        Matriz result(size_rows, size_columns);
        for (int i = 0; i < size_rows*size_columns; i++) {
            result.data[i] = data[i] + m.data[i];
        }
        return result;
    }

    Matriz<T> operator-(const Matriz<T>& m) const {
        if (m.size_rows != size_rows || m.size_columns != size_columns) {
            throw std::invalid_argument(
                "Number of rows and columns must be the same in matrices being subtracted"
            );
        }
        Matriz result(size_rows, size_columns);
        for (int i = 0; i < size_rows*size_columns; i++) {
            result.data[i] = data[i] - m.data[i];
        }
        return result;
    }

    Matriz<T>& operator+=(const Matriz<T>& m) {
        if (m.size_rows != size_rows || m.size_columns != size_columns) {
            throw std::invalid_argument(
                "Number of rows and columns must be the same in matrices being summed"
            );
        }
        for (int i = 0; i < size_rows*size_columns; i++) {
            data[i] = data[i] + m.data[i];
        }
        return *this;
    }

    Matriz<T>& operator-=(const Matriz<T>& m) {
        if (m.size_rows != size_rows || m.size_columns != size_columns) {
            throw std::invalid_argument(
                "Number of rows and columns must be the same in matrices being subtracted"
            );
        }
        for (int i = 0; i < size_rows*size_columns; i++) {
            data[i] = data[i] - m.data[i];
        }
        return *this;
    }

    Matriz<T> transpose() const {
        Matriz result(size_columns, size_rows);

        for (int i = 0; i < size_rows; i++) {
            for (int j = 0; j < size_columns; j++) {
                result.set(j, i, data[i*size_columns + j]);
            }
        }

        return result;   
    }

    void print() {
        for (int i = 0; i < size_rows; i++) {
            for (int j = 0; j < size_columns; j++) {
                cout << data[i*size_columns + j] << " ";
            }
            cout << endl;
        }
    }
};


int main() {
    Matriz<int> m1(2, 3);
    Matriz<int> m2(2, 3);

    m1.set(0, 0, 10); m1.set(0, 1, 20); m1.set(0, 2, 30);
    m1.set(1, 0, 40); m1.set(1, 1, 50); m1.set(1, 2, 60);

    cout << "Imprimiendo matriz m1:" << endl;
    m1.print();

    m2.set(0, 0, 10); m2.set(0, 1, 15); m2.set(0, 2, 20);
    m2.set(1, 0, 25); m2.set(1, 1, 30); m2.set(1, 2, 35);

    cout << "Imprimiendo matriz m2:" << endl;
    m2.print();

    cout << "Imprimiento elemento [1,1] de matriz m2:" << endl;
    cout << m2.get(1, 1) << endl;
    
    Matriz<int> m3(2,3);
    m3 = m2;
    cout << "Imprimiendo matriz m3 igual a m2" << endl;
    m3.print();

    Matriz<int> m4 = m1 + m2;
    cout << "Imprimiendo matriz m4 igual a suma de m1 y m2" << endl;
    m4.print();

    Matriz<int> m5 = m1 - m2;
    cout << "Imprimiendo matriz m5 igual a resta de m1 y m2" << endl;
    m5.print();

    m1 += m2;
    cout << "Imprimiendo matriz m1 despues de sumarle m2" << endl;
    m1.print();

    m1 -= m2;
    cout << "Imprimiendo matriz m1 despues de restarle m2 (teniendo en cuenta que se le sumo en el paso anterior)" << endl;
    m1.print();

    cout << "Imprimiendo transpuesta de m1 despues de como quedo en el ultimo paso" << endl;
    m1.transpose().print();

    return 0;
}
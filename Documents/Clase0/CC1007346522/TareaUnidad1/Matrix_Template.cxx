#include<iostream>

using namespace std;

template<class Template> class Matrix {

private:

    Template* Data;
    int Dim_x;
    int Dim_y;

public:
    Matrix(Template Data);

}
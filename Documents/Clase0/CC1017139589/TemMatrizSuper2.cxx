#include<iostream>
#include<array>

using namespace std;

template <typename T> class Matrix{
  T* matrix = nullptr;
  int cols = 0;
  int rows = 0;
  public:
  Matrix();
  Matrix(int cols, int rows);
  Matrix(const Matrix& mat);
  ~Matrix();
  T GetElement(int row, int col);
  void SetElement(int row, int col, T value);
  void PrintMatrix();
  const Matrix& operator=(const Matrix& mat);
  Matrix operator+(const Matrix& oper);
};

template <typename T>Matrix<T>::Matrix(){
    this->cols = 3;
    this->rows = 3;
    matrix = new T[9];
    for(int i=0; i<9; i++){
        *(matrix+i) = i+1;        
    }
}

template <typename T>Matrix<T>::Matrix(int cols, int rows){
    this->cols = cols;
    this->rows = rows;
    matrix = new T[cols*rows];
    for(int i=0; i<cols*rows; i++){
        *(matrix+i) = i+1;        
    }
}

template <typename T>Matrix<T>::Matrix(const Matrix& mat){
    if(this != &mat){
        this->cols = mat.cols;
        this->rows = mat.rows;
    
        this->matrix = new T[this->cols*this->rows];
        for(int i= 0; i<(this->cols*this->rows); i++){
            *(matrix+i) = *((mat.matrix)+i);
        }
    }
}

template <typename T>Matrix<T>::~Matrix(){
    delete[] matrix;
    matrix = nullptr;
}

template <typename T> T Matrix<T>::GetElement(int row, int col){ 
    return *(matrix+(row*this->cols)+col);        
}

template <typename T> void Matrix<T>::SetElement(int row, int col, T value){ 
    *(matrix+(row*this->cols)+col) = value;        
}

template <typename T>void Matrix<T>::PrintMatrix(){
    for(int i=0; i< (this->cols*this->rows);i++){
        cout<<"["<<*(matrix+i)<<"],";
    }
    cout<<endl;
}

template <typename T> const Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat){
    if(this != &mat){
        cout<<"calling the overloaded assignment operator"<<endl;
        this->cols = mat.cols;
        this->rows = mat.rows;
        if(this->matrix != nullptr){
            delete[] this->matrix;
            this->matrix = nullptr;
        }
        this->matrix = new T[this->cols*this->rows];
        for(int i= 0; i<(this->cols*this->rows); i++){
            *(matrix+i) = *((mat.matrix)+i);
        }
    }
    return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator+(const Matrix<T>& oper){
    int sizeThis = this->cols*this->rows;
    int sizeOper = oper.cols*oper.rows;
    Matrix result(this->rows, this->cols);
    if(sizeThis == sizeOper){
        for(int i=0; i<sizeThis; i++){
            *(result.matrix+i) = *(this->matrix+i) + *(oper.matrix+i);
        }
    }
    return result;
}

int main(){
    Matrix<int> m(3,3);
    m.PrintMatrix();
    cout<<"Matrix m[0,1] = "<<m.GetElement(0,1)<<endl;
    cout<<"Matrix m[1,2] = "<<m.GetElement(1,2)<<endl;
    cout<<"Matrix m[2,0] = "<<m.GetElement(2,0)<<endl;
    m.SetElement(2,0,25);
    cout<<"Matrix m[2,0] = "<<m.GetElement(2,0)<<endl;
    Matrix<int> m2;
    m2 = m;
    m2.PrintMatrix();
    Matrix<int> m3;
    m3 = m+m2;
    m3.PrintMatrix();
}
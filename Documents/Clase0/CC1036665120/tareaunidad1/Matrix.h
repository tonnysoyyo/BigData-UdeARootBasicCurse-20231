#include <iostream>

template <typename T>
class Matrix
{
private:
    T *data;
    int size_row;
    int size_column;
    int size;

protected:
    void verifyOperations(const Matrix<T> &m) const;
    void verifyGetOrSet(unsigned int row, unsigned int colum) const;

public:
    // ------------------------
    // ----- Constructor -------
    // ------------------------
    Matrix(unsigned int row, unsigned int colum) : size(row * colum)
    {

        this->size_row = row;
        this->size_column = colum;

        data = new T[row * colum];

        for (unsigned int i = 0; i < this->size; i++)
        {
            data[i] = 0.0;
        }
    }

    ~Matrix()
    {
        delete[] data;
    }

    // ------------------------
    // ------- Methods ---------
    // ------------------------

    T get(unsigned int row, unsigned int colum) const;

    void set(unsigned int row, unsigned int colum, T value);

    void print();

    // ------------------------

    Matrix<T> operator+(const Matrix<T> &m) const
    {
        Matrix m_new(this->size_row, this->size_column);

        try
        {
            this->verifyOperations(m);

            for (unsigned int i = 0; i < this->size; i++)
            {
                m_new.data[i] = data[i] + m.data[i];
            }
        }
        catch (const char *error_message)
        {
            std::cerr << "Error: " << error_message << std::endl;
        }

        return m_new;
    }

    // ------------------------

    Matrix<T> operator-(const Matrix<T> &m) const
    {

        Matrix m_new(this->size_row, this->size_column);

        try
        {
            this->verifyOperations(m);

            for (unsigned int i = 0; i < this->size; i++)
            {
                m_new.data[i] = data[i] - m.data[i];
            }
        }
        catch (const char *error_message)
        {
            std::cerr << "Error: " << error_message << std::endl;
        }

        return m_new;
    }

    // ------------------------

    Matrix<T> &operator=(const Matrix<T> &m)
    {

        if (this != &m)
        {
            delete[] data;
            size_row = m.size_row;
            size_column = m.size_column;
            size = m.size;
            data = new T[size];
            for (unsigned int i = 0; i < size; i++)
            {
                data[i] = m.data[i];
            }
        }

        return *this;
    }

    // --------------------------

    Matrix<T> &operator+=(const Matrix<T> &m)
    {
        try
        {
            this->verifyOperations(m);

            for (unsigned int i = 0; i < this->size; i++)
            {
                data[i] = m.data[i] + data[i];
            }
        }
        catch (const char *error_message)
        {
            std::cerr << "Error: " << error_message << std::endl;
        }

        return *this;
    }

    // --------------------------

    Matrix<T> &operator-=(const Matrix<T> &m)
    {
        try
        {
            this->verifyOperations(m);

            for (unsigned int i = 0; i < this->size; i++)
            {
                data[i] -= m.data[i];
            }
        }
        catch (const char *error_message)
        {
            std::cerr << "Error: " << error_message << std::endl;
        }

        return *this;
    }
};

// --------------------------
// --- Getter and setter ----
// --------------------------
template <class T>
T Matrix<T>::get(unsigned int row, unsigned int colum) const
{
    try
    {
        this->verifyGetOrSet(row, colum);

        // skips the previous rows of the matrix.
        // Adds the number of columns until it reaches the required data.
        return data[this->size_column * (row) + (colum)];
    }
    catch (const char *error_message)
    {
        std::cerr << "Error: " << error_message << std::endl;
        return 0;
    }
};

template <class T>
void Matrix<T>::set(unsigned int row, unsigned int colum, T value)
{
    try
    {
        this->verifyGetOrSet(row, colum);
        data[this->size_column * (row) + (colum)] = value;
    }
    catch (const char *error_message)
    {
        std::cerr << "Error: " << error_message << std::endl;
    }
};

// --------------------------
// --------- PRINT ---------
// --------------------------
template <class T>
void Matrix<T>::print()
{
    std::cout << "--- MATRIX --" << std::endl;
    std::cout << "-------------" << std::endl;

    for (unsigned int i = 0; i < this->size; i++)
    {
        if ((i + 1) % (this->size_column) != 0.0)
        {
            std::cout << data[i] << " ";
        }
        else
        {
            std::cout << data[i] << std::endl;
        }
    }

    std::cout << "-------------" << std::endl;
};

// --------------------------
// --------- verify ---------
// --------------------------
template <class T>
void Matrix<T>::verifyOperations(const Matrix<T> &m) const
{
    if (this->size_column != m.size_column || this->size_row != m.size_row)
    {
        throw "No se puede realizar esta operación. Las matrices deben tener la misma dimensión";
    }
};

template <class T>
void Matrix<T>::verifyGetOrSet(unsigned int row, unsigned int colum) const
{
    if (colum >= this->size_column || row >= this->size_row)
    {
        throw "El índice ingresado es mayor a la dimensión de la matriz";
    }
};
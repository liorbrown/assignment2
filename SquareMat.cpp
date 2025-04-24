#include <stdexcept>
#include "SquareMat.hpp"

using namespace Matrix;
using namespace std;

SquareMat::SquareMat(size_t rows, size_t cols) : rows(rows), cols(cols){
    if (!rows || !cols)
        throw invalid_argument("Arguments must be positives 🫤");

    this->allocateMem();
}

void SquareMat::allocateMem()
{
    this->mat = new double *[rows];
    
    for (size_t i = 0; i < rows; i++)
        this->mat[i] = new double[cols]{0}; 
}

void SquareMat::freeMem()
{
    if (this->mat)
    {
        for (size_t i = 0; i < this->rows; i++)
            if (this->mat[i])
                delete[] this->mat[i];
                
        delete[] this->mat;
    }
}

void SquareMat::copyMem(const SquareMat &other)
{
    for (size_t i = 0; i < this->rows; i++)
        for (size_t j = 0; j < this->cols; j++)
            (*this)[i][j] = other[i][j];
}

double* SquareMat::operator[](size_t row) const
{
    return this->mat[row];
}

SquareMat SquareMat::operator-() const
{
    return SquareMat(0,0);
}

SquareMat SquareMat::operator+(const SquareMat &) const
{
    return SquareMat(0,0);
}

SquareMat SquareMat::operator*(const SquareMat &) const
{
    return SquareMat(0,0);
}

SquareMat SquareMat::operator%(const SquareMat &) const
{
    return SquareMat(0,0);
}

SquareMat SquareMat::operator%(int) const
{
    return SquareMat(0,0);
}

SquareMat SquareMat::operator/(int) const
{
    return SquareMat(0,0);
}

SquareMat SquareMat::operator^(size_t) const
{
    return SquareMat(0,0);
}

SquareMat SquareMat::operator~() const
{
    return SquareMat(0,0);
}

double SquareMat::operator!() const
{
    return 0.0;
}

SquareMat& SquareMat::operator-=(const SquareMat &)
{
    return (*this);
}

SquareMat& SquareMat::operator+=(const SquareMat &)
{
    return (*this);
}

SquareMat& SquareMat::operator++()
{
    return (*this);
}

SquareMat& SquareMat::operator++(int)
{
    return (*this);
}

SquareMat& SquareMat::operator--()
{
    return (*this);
}

SquareMat& SquareMat::operator--(int)
{
    return (*this);
}

SquareMat& SquareMat::operator*=(const SquareMat &)
{
    return (*this);
}

SquareMat& SquareMat::operator*=(double)
{
    return (*this);
}

SquareMat& SquareMat::operator%=(const SquareMat &)
{
    return (*this);
}

SquareMat& SquareMat::operator%=(int)
{
    return (*this);
}

bool SquareMat::operator==(const SquareMat &) const
{
    return false;
}

bool SquareMat::operator!=(const SquareMat &) const
{
    return false;
}

bool SquareMat::operator<(const SquareMat &) const
{
    return false;
}

bool SquareMat::operator<=(const SquareMat &) const
{
    return false;
}

bool SquareMat::operator>(const SquareMat &) const
{
    return false;
}

bool SquareMat::operator>=(const SquareMat &) const
{
    return false;
}

SquareMat& SquareMat::operator=(const SquareMat &other)
{
    if (this != &other)
    {
        if (this->rows != other.rows || this->cols != other.cols)
        {
            this->freeMem(); 
            
            this->rows = other.rows;
            this->cols = other.cols;
            this->allocateMem();
        }

        this->copyMem(other);
    }

    return *this;
}

SquareMat operator*(const double scalar,const SquareMat& mat)
{
    return mat;
}

ostream& operator<<(ostream& stream, SquareMat mat)
{
    return (stream);
}

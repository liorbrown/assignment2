#include <stdexcept>
#include <cmath>
#include "SquareMat.hpp"

namespace Matrix{
    SquareMat::SquareMat(size_t size) : size(size){
        if (!size)
            throw invalid_argument("Matrix size must be positive 🫤");

        this->allocateMem();
    }

    SquareMat& SquareMat::operator=(const SquareMat &other)
    {
        if (this != &other)
        {
            if (this->size != other.size)
            {
                this->freeMem(); 
                
                this->size = other.size;
                this->allocateMem();
            }

            this->copyMem(other);
        }

        return *this;
    }

    void SquareMat::allocateMem()
    {
        this->mat = new double* [this->size];
        
        for (size_t i = 0; i < this->size; i++)
            this->mat[i] = new double[this->size]{0.0}; 
    }

    void SquareMat::freeMem()
    {
        if (this->mat)
        {
            for (size_t i = 0; i < this->size; i++)
                if (this->mat[i])
                    delete[] this->mat[i];
                    
            delete[] this->mat;
        }
    }

    void SquareMat::copyMem(const SquareMat &other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices not in the same size 🫤");

        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] = other[i][j];
    }

    double SquareMat::getSum() const
    {
        double result = 0;

        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                result += (*this)[i][j];
        
        return result;
    }

    SquareMat *SquareMat::getMinor(const size_t col) const
    {
        if (this->size == 1)
            throw invalid_argument("Can't calculate minor for matrix in size 1 🫤");
        
        SquareMat* result = new SquareMat(this->size - 1);

        for (size_t i = 0; i < this->size - 1; i++)
            for (size_t j = 0; j < this->size - 1; j++)
                (*result)[i][j] = (*this)[i + 1][j < col ?  j : j + 1];            
        
        return result;
    }

    SquareMat& SquareMat::operator-=(const SquareMat& other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices not in the same size 🫤");
        
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] -= other[i][j];                                
        
        return (*this);
    }

    SquareMat& SquareMat::operator+=(const SquareMat& other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices not in the same size 🫤");
        
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] += other[i][j];                                
        
        return (*this);
    }

    SquareMat& SquareMat::operator%=(const SquareMat& other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices not in the same size 🫤");
        
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] *= other[i][j];                                
        
        return (*this);
    }

    SquareMat& SquareMat::operator%=(const int scalar)
    {
        if (!scalar)
            throw invalid_argument("Can't divide by zero 🫤");
        
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] = fmod((*this)[i][j], scalar);
        
        return (*this);
    }

    SquareMat& SquareMat::operator/=(const double scalar)
    {
        if (!scalar)
            throw invalid_argument("Can't divide by zero 🫤");
        
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] /= scalar;                                
        
        return (*this);
    }

    SquareMat& SquareMat::operator++()
    {
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j]++;
        
        return (*this);
    }

    SquareMat SquareMat::operator++(int)
    {
        SquareMat result{*this};

        ++*this;

        return (result);
    }

    SquareMat& SquareMat::operator--()
    {
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j]--;
        
        return (*this);
    }

    SquareMat SquareMat::operator--(int)
    {
        SquareMat result{*this};

        --*this;

        return (result);
    }

    SquareMat& SquareMat::operator*=(const double scalar)
    {
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] *= scalar;
        
        return (*this);
    }

    SquareMat& SquareMat::operator*=(const SquareMat& other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices sizes not fit to by multipied 🫤");

        SquareMat copy{*this};
                
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
            {
                (*this)[i][j] = 0.0;

                for (size_t k = 0; k < this->size; k++)
                    (*this)[i][j] += (copy[i][k] * other[k][j]);
            }
        
        return (*this);
    }

    SquareMat SquareMat::operator-() const
    {
        SquareMat result{this->size};

        return (result -= *this);
    }

    bool SquareMat::operator==(const SquareMat& other) const
    {
        return (this->getSum() == other.getSum());
    }

    bool SquareMat::operator!=(const SquareMat& other) const
    {
        return (this->getSum() != other.getSum());
    }

    bool SquareMat::operator<(const SquareMat& other) const
    {
        return (this->getSum() < other.getSum());
    }

    bool SquareMat::operator<=(const SquareMat& other) const
    {
        return (this->getSum() <= other.getSum());
    }

    bool SquareMat::operator>(const SquareMat& other) const
    {
        return (this->getSum() > other.getSum());
    }

    bool SquareMat::operator>=(const SquareMat& other) const
    {
        return (this->getSum() >= other.getSum());
    }

    SquareMat SquareMat::operator^(const size_t exp)
    {
        SquareMat result{this->size};

        for (size_t i = 0; i < this->size; i++)
            result[i][i] = 1.0;
        
        for (size_t i = 0; i < exp; i++)
            result *= *this;
        
        return result;
    }

    double SquareMat::operator!() const
    {
        if (this->size == 1)
            return (*this)[0][0];
        
        double result = 0;

        for (size_t i = 0; i < this->size; i++)
        {
            SquareMat* minor = this->getMinor(i);

            result += (pow(-1, i) * (*this)[0][i] * !(*minor));

            delete minor;
        }
        
        return result;
    }

    ostream& operator<<(ostream& stream, const SquareMat& mat)
    {
        stream << endl;

        for (size_t j = 0; j < 9 * mat.size + 1; j++)
                stream << '-';
            
        stream << endl;

        for (size_t i = 0; i < mat.size; i++)
        {
            for (size_t j = 0; j < mat.size; j++)
                stream << '|' << to_string(mat[i][j]);

            stream << '|' << endl;

            for (size_t j = 0; j < 9 * mat.size + 1; j++)
                stream << '-';
            
                stream << endl;
        }
        
        return (stream);
    }

    SquareMat operator-(SquareMat left, const SquareMat &right)
    {
        return (left -= right);
    }

    SquareMat operator+(SquareMat left, const SquareMat &right)
    {
        return (left += right);
    }

    SquareMat operator*(SquareMat left, const SquareMat& right)
    {
        return (left *= right);
    }

    SquareMat operator*(SquareMat mat, const double scalar)
    {
        return (mat *= scalar);
    }

    SquareMat operator*(const double scalar,const SquareMat& mat)
    {
        return (mat * scalar);
    }

    SquareMat operator%(SquareMat left, const SquareMat& right)
    {
        return (left %= right);
    }

    SquareMat operator%(SquareMat mat, const int scalar)
    {
        return (mat %= scalar);
    }

    SquareMat operator/(SquareMat mat, const double scalar)
    {
        return (mat /= scalar);
    }

    SquareMat operator~(SquareMat mat)
    {
        for (size_t i = 0; i < mat.size - 1; i++)
            for (size_t j = i + 1; j < mat.size; j++)
            {
                double temp = mat[i][j];
                mat[i][j] = mat[j][i];
                mat[j][i] = temp;
            }                                
        
        return mat;
    }  
}
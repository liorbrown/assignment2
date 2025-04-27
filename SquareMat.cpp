// liorbrown@outlook.co.il

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
        // Ensure that not making self assingment
        if (this != &other)
        {
            // If other matrix is not in the same size, need to free this matrix memory,
            // and allocate new one in the right size.
            // Otherwise n+ot need new allocation,
            // but only override existing data with new one
            if (this->size != other.size)
            {
                // Need to free memory before update matrix size
                this->freeMem(); 
                
                // Need to allocate new memory after update matrix size
                this->size = other.size;
                this->allocateMem();
            }

            this->copyMem(other);
        }

        // Return reference to this for enable concatenation
        return *this;
    }

    void SquareMat::allocateMem()
    {
        // Creates rows array
        this->mat = new double* [this->size];
        
        // Foreach row creates its columns array, and init all cells with zero
        for (size_t i = 0; i < this->size; i++)
            this->mat[i] = new double[this->size]{0.0}; 
    }

    void SquareMat::freeMem()
    {
        if (this->mat)
        {
            // Free each row's columns array
            for (size_t i = 0; i < this->size; i++)
                if (this->mat[i])
                    delete[] this->mat[i];
            
            // Free the rows array
            delete[] this->mat;
        }
    }

    void SquareMat::copyMem(const SquareMat &other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices not in the same size 🫤");

        // Deep copy value of each cell from other to this
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] = other[i][j];
    }

    double SquareMat::getSum() const
    {
        double result = 0;

        // Runs on each cell and summerize all values
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                result += (*this)[i][j];
        
        return result;
    }

    SquareMat* SquareMat::getMinor(const size_t col) const
    {
        if (this->size == 1)
            throw invalid_argument("Can't calculate minor for matrix in size 1 🫤");
        
        // The minor is always in this size minus one
        size_t minorSize = this->size - 1;
        
        SquareMat* result = new SquareMat(minorSize);

        // Run on each cell of new minor matrix
        for (size_t i = 0; i < minorSize; i++)
            for (size_t j = 0; j < minorSize; j++)
                // This minor is work only for first row, so the row of each cell in minor matrix
                // contains the value of cell in row i + 1 in origin matrix.
                // The column index depends if current column less than given column
                // so take the same column as original,
                // Oterwise, skip the given column to next one
                (*result)[i][j] = (*this)[i + 1][j < col ?  j : j + 1];            
        
        return result;
    }

    SquareMat& SquareMat::operator-=(const SquareMat& other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices not in the same size 🫤");
        
        // Runs on each matrix cell, 
        // and subtruct the value of corresponding cell in other matrix
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] -= other[i][j];                                
        
        return (*this);
    }

    SquareMat& SquareMat::operator+=(const SquareMat& other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices not in the same size 🫤");
        
        // Runs on each matrix cell, 
        // and add the value of corresponding cell in other matrix
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] += other[i][j];                                
        
        return (*this);
    }

    SquareMat& SquareMat::operator%=(const SquareMat& other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices not in the same size 🫤");
        
        // Runs on each matrix cell, 
        // and multiply it with the value of corresponding cell in other matrix
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] *= other[i][j];                                
        
        return (*this);
    }

    SquareMat& SquareMat::operator%=(const int scalar)
    {
        if (!scalar)
            throw invalid_argument("Can't divide by zero 🫤");
        
        // Runs on each matrix cell, and modulo it by given scalar
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] = fmod((*this)[i][j], scalar);
        
        return (*this);
    }

    SquareMat& SquareMat::operator/=(const double scalar)
    {
        if (!scalar)
            throw invalid_argument("Can't divide by zero 🫤");
        
        // Runs on each matrix cell, and divide it by given scalar
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] /= scalar;                                
        
        return (*this);
    }

    SquareMat& SquareMat::operator++()
    {
        // Runs on each matrix cell, and increase it by 1
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j]++;
        
        return (*this);
    }

    SquareMat SquareMat::operator++(int)
    {
        // Save copy of this matrix
        SquareMat result{*this};

        // Increase this matrix
        ++*this;

        // Return copy
        return (result);
    }

    SquareMat& SquareMat::operator--()
    {
        // Runs on each matrix cell, and decrease it by 1
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j]--;
        
        return (*this);
    }

    SquareMat SquareMat::operator--(int)
    {
        // Save copy of this matrix
        SquareMat result{*this};

        // Decrease this matrix
        --*this;

        // Return copy
        return (result);
    }

    SquareMat& SquareMat::operator*=(const double scalar)
    {
        // Runs on each matrix cell, and multiply it by scalar
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
                (*this)[i][j] *= scalar;
        
        return (*this);
    }

    SquareMat& SquareMat::operator*=(const SquareMat& other)
    {
        if (this->size != other.size)
            throw invalid_argument("Matrices sizes not fit to by multipied 🫤");

        // Save copy of origin matrix for needed calculation
        SquareMat copy{*this};
                
        // Runs on each cell this in matrix
        for (size_t i = 0; i < this->size; i++)
            for (size_t j = 0; j < this->size; j++)
            {
                (*this)[i][j] = 0.0;

                // Runs on the corresponding row in this matrix,
                // and corresponding column in other matrix
                // and sumerrize multiply values
                for (size_t k = 0; k < this->size; k++)
                    (*this)[i][j] += (copy[i][k] * other[k][j]);
            }
        
        return (*this);
    }

    SquareMat SquareMat::operator-() const
    {
        // Create zero matrix in same size ad this
        SquareMat result{this->size};

        // Return the subtraction of zero matrix with this matrix
        return (result -= *this);
    }

    bool SquareMat::operator==(const SquareMat& other) const
    {
        // Check only the sum of matrices, not their cells values
        return (this->getSum() == other.getSum());
    }

    bool SquareMat::operator!=(const SquareMat& other) const
    {
        // Check only the sum of matrices, not their cells values
        return (this->getSum() != other.getSum());
    }

    bool SquareMat::operator<(const SquareMat& other) const
    {
        // Check only the sum of matrices, not their cells values
        return (this->getSum() < other.getSum());
    }

    bool SquareMat::operator<=(const SquareMat& other) const
    {
        // Check only the sum of matrices, not their cells values
        return (this->getSum() <= other.getSum());
    }

    bool SquareMat::operator>(const SquareMat& other) const
    {
        // Check only the sum of matrices, not their cells values
        return (this->getSum() > other.getSum());
    }

    bool SquareMat::operator>=(const SquareMat& other) const
    {
        // Check only the sum of matrices, not their cells values
        return (this->getSum() >= other.getSum());
    }

    SquareMat SquareMat::operator^(const size_t exp)
    {
        SquareMat result{this->size};

        // Creates new identity matrix with this matrix size
        for (size_t i = 0; i < this->size; i++)
            result[i][i] = 1.0;
        
        // Multiply identity matrix exp times by this matrix
        for (size_t i = 0; i < exp; i++)
            result *= *this;
        
        return result;
    }

    double SquareMat::operator!() const
    {
        // This is recursion stop condition
        if (this->size == 1)
            return (*this)[0][0];
        
        double result = 0;

        // This determinant function calculate always with first row,
        // So make one loop for each row's cells
        for (size_t i = 0; i < this->size; i++)
        {
            SquareMat* minor = this->getMinor(i);

            // Calculate determinant by recursion call for this cell minor
            result += (pow(-1, i) * (*this)[0][i] * !(*minor));

            delete minor;
        }
        
        return result;
    }

    ostream& operator<<(ostream& stream, const SquareMat& mat)
    {
        stream << endl;

        // Print first row delimiter
        for (size_t j = 0; j < 9 * mat.getSize() + 1; j++)
                stream << '-';
            
        stream << endl;

        // Runs on each row
        for (size_t i = 0; i < mat.getSize(); i++)
        {
            // Runs on each row's cell and print its value
            // the using of to_string make it print same number of digits after point
            // make it more pretty
            for (size_t j = 0; j < mat.getSize(); j++)
                stream << '|' << to_string(mat[i][j]);

            stream << '|' << endl;

            // Print row delimiter
            for (size_t j = 0; j < 9 * mat.getSize() + 1; j++)
                stream << '-';
            
            stream << endl;
        }
        
        return (stream);
    }

    SquareMat operator-(SquareMat left, const SquareMat &right)
    {
        // Substructs right from left copy, and returns copy of left copy
        return (left -= right);
    }

    SquareMat operator+(SquareMat left, const SquareMat &right)
    {
        // Adds right to left copy, and returns copy of left copy
        return (left += right);
    }

    SquareMat operator*(SquareMat left, const SquareMat& right)
    {
        // Multiply left copy by right, and returns copy of left copy
        return (left *= right);
    }

    SquareMat operator*(SquareMat mat, const double scalar)
    {
        // Multiply mat copy by scalar, and returns copy of mat copy
        return (mat *= scalar);
    }

    SquareMat operator*(const double scalar,const SquareMat& mat)
    {
        // Calls operator* with reverse parametrs order
        return (mat * scalar);
    }

    SquareMat operator%(SquareMat left, const SquareMat& right)
    {
        // Multiply elements of mat copy by right, and returns copy of left copy
        return (left %= right);
    }

    SquareMat operator%(SquareMat mat, const int scalar)
    {
        // Modulo mat copy by scalar, and returns copy of mat copy
        return (mat %= scalar);
    }

    SquareMat operator/(SquareMat mat, const double scalar)
    {
        // Divide mat copy by scalar, and returns copy of mat copy
        return (mat /= scalar);
    }

    SquareMat operator~(SquareMat mat)
    {
        // Runs on each cell that is right to main diagonl
        for (size_t i = 0; i < mat.getSize() - 1; i++)
            for (size_t j = i + 1; j < mat.getSize(); j++)
            {
                // Swap current cell with its transpose cell
                double temp = mat[i][j];
                mat[i][j] = mat[j][i];
                mat[j][i] = temp;
            }                                
        
        // Returns copy of mat copy
        return mat;
    }  
}
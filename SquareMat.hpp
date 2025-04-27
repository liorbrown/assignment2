// liorbrown@outlook.co.il

#include <cstddef>
#include <iostream>

using namespace std;

namespace Matrix{

    /// @brief This class represents a real numbers square matrix, 
    /// and it includes operators for performing arithmetic operations on matrices.
    class SquareMat{
        private:
            size_t size;
            double** mat;

            /// @brief allocate memory for the matrix
            void allocateMem();

            /// @brief Free matrix memory
            void freeMem();

            /// @brief Copy memory from other natrix to this matrix
            /// @param other Other matrix to copy data from
            void copyMem(const SquareMat& other);

            /// @brief Get sum of all matrix numbers
            /// @return The sum of all numbers in the matrix
            double getSum() const;

            /// @brief Get minor of this matrix, for the cell in row 0 and column col
            /// @param col The column index to do the minor on it
            /// @return The minor matrix of this matrix for cell (0,col)
            SquareMat* getMinor(const size_t col) const;
            
        public:

            /// @brief Ctor - creates square matrix in with given size.
            /// All cells initialize to zero
            /// @param size The size of the new matrix
            SquareMat(size_t size);

            /// @brief Copy constructor
            /// @param Other matrix to copy from it
            SquareMat(const SquareMat& other): SquareMat(other.size) {this->copyMem(other);}

            /// @brief Assignment operator
            /// @param Other matrix to copy data from it 
            /// @return This matrix
            SquareMat& operator=(const SquareMat& other);

            /// @brief Dtor - free matrix memory
            ~SquareMat(){ this->freeMem();}
            
            size_t getSize() const {return this->size;} 

            /// @brief Return matrix row, given row index
            /// can use it by adding another [] to the return value for get cell data
            /// @param row Index of wanted row
            /// @return Pointer to the wanted row
            double* operator[](size_t row) const {return this->mat[row];}

            // ---------------- Self assignment operators ----------------------

            /// @brief Substruct other matrix from this matrix, by substruct value of each cell
            /// by its corresponding cell in the other matrix
            /// @param other Other matrix to subtruct from this matrix
            /// @return This matrix after substruction
            SquareMat& operator-=(const SquareMat& other);

            /// @brief Summerize other matrix with this matrix, by Summerize value of each cell
            /// by its corresponding cell in the other matrix
            /// @param other Other matrix to Summerize to this matrix
            /// @return This matrix after Summerize
            SquareMat& operator+=(const SquareMat& other);

            /// @brief Increase by one every cell in matrix
            /// @return This matrix after increasing
            SquareMat& operator++();
            
            /// @brief Increase by one every cell in matrix
            /// @param dummy This dummy makes this operator to be mat++ rather then ++mat
            /// @return Clone of this matrix before increasing
            SquareMat operator++(int dummy);

            /// @brief Decrease by one every cell in matrix
            /// @return This matrix after decreasing
            SquareMat& operator--();

            /// @brief Decrease by one every cell in matrix
            /// @param dummy This dummy makes this operator to be mat-- rather then --mat
            /// @return Clone of this matrix before decreasing
            SquareMat operator--(int);

            /// @brief Multipy this matrix by other matrix, using standard matrix multiplication
            /// @param other Other matrix to muliply by it
            /// @return This matrix after muliplying
            SquareMat& operator*=(const SquareMat& other);

            /// @brief Multipy this matrix by scalar, by multiply each  cell by the scalar
            /// @param scalar The scalar to multliply by 
            /// @return This matrix after muliplying
            SquareMat& operator*=(const double scalar);

            /// @brief Divide this matrix by scalar, by dividing each cell by the scalar
            /// @param scalar The scalar to divide by 
            /// @return This matrix after dividing
            SquareMat& operator/=(const double scalar);

            /// @brief Modulo this matrix by scalar, by modulo each cell by the scalar
            /// @param scalar The scalar to modulo by 
            /// @return This matrix after modulo
            SquareMat& operator%=(const int scalar);

            /// @brief Multiply this matrix by other matix, by multiply value of each cell
            /// by its corresponding cell in the other matrix
            /// @param other Other matrix to multiply to this matrix
            /// @return This matrix after multiplying
            SquareMat& operator%=(const SquareMat& other);
            
            // ---------------- Equality operators ----------------------

            /// @brief Check if matrix numbers sum is equal between this and other matrix 
            /// @param other Other matrix to compare to
            /// @return True - if sum equal, False - otherwise
            bool operator==(const SquareMat& other) const;

            /// @brief Check if matrix numbers sum is not equal between this and other matrix 
            /// @param other Other matrix to compare to
            /// @return True - if sum is not equal, False - otherwise
            bool operator!=(const SquareMat& other) const;

            /// @brief Check if this matrix numbers sum is smaller than other matrix 
            /// @param other Other matrix to compare to
            /// @return True - if sum smaller, False - otherwise
            bool operator<(const SquareMat& other) const;

            /// @brief Check if this matrix numbers sum is smaller or equal than other matrix 
            /// @param other Other matrix to compare to
            /// @return True - if sum smaller or equal, False - otherwise
            bool operator<=(const SquareMat& other) const;

            /// @brief Check if this matrix numbers sum is greater than other matrix 
            /// @param other Other matrix to compare to
            /// @return True - if sum greater, False - otherwise
            bool operator>(const SquareMat& other) const;

            /// @brief Check if this matrix numbers sum is greater or equal than other matrix 
            /// @param other Other matrix to compare to
            /// @return True - if sum greater or equal, False - otherwise
            bool operator>=(const SquareMat& other) const;

            // ---------------- Unary operators ----------------------

            /// @brief Return the minus of this marix, 
            /// i.e in every cell will be the negative of original cell
            /// @return New matrix that represent the minus of this marix
            SquareMat operator-() const;

            /// @brief Return the determinant of this matrix
            /// @return The determinant of this matrix
            double operator!() const;

            /// @brief Return matrix of this matrix power given exponent 
            /// @param exp The number of time to multiply this matrix with itself
            /// @return New matrix that represent the result of this matrix power the exponent
            SquareMat operator^(const size_t exp); 
    };

    // ---------------- Out class operators ----------------------

    /// @brief Return the Substruction of right matrix from left matrix, by substruct value of each cell
    /// by its corresponding cell in the other matrix
    /// @param left Matrix to subtruct from it
    /// @param right Matrix to subtruct from left matrix
    /// @return New matrix that represent Substruction result
    SquareMat operator-(SquareMat left, const SquareMat& right);

    /// @brief Return the Summerize of 2 matrices, by summerize value of each pair of cells
    /// in the corresponding cells
    /// @param left Left matrix to summerize from it
    /// @param right Right matrix to summerize from it
    /// @return New matrix that represent summerize result
    SquareMat operator+(SquareMat left, const SquareMat& right);

    /// @brief Return the result of right matrix multliply left matrix, 
    /// using standard matrix multiplication
    /// @param left Matrix to multiply
    /// @param right Matrix to be multiply by
    /// @return New matrix that represent result of matrix multiplication
    SquareMat operator*(SquareMat left, const SquareMat& right);        

    /// @brief Return the result of multiply matrix by scalar
    /// @param mat Matrix to multiply
    /// @param scalar Scalar to multiply the matrix with it
    /// @return New matrix that represent multiplication result
    SquareMat operator*(SquareMat mat, const double scalar); 
    
    /// @brief Return the result of multiply matrix by scalar
    /// @param scalar Scalar to multiply the matrix with it
    /// @param mat Matrix to multiply
    /// @return New matrix that represent multiplication result
    SquareMat operator*(const double scalar,const SquareMat& mat);        

    /// @brief Return the result of 2 matrices elements multliply, 
    /// by multiply value of each pair of cells in the corresponding cells
    /// @param left Matrix to multiply
    /// @param right Matrix to multiply
    /// @return New matrix that represent result of matrices element multiplication
    SquareMat operator%(SquareMat left, const SquareMat& right);

    /// @brief Return the result of modulo matrix by scalar, by modulo each cell by given scalar
    /// @param mat Matrix to make modulo
    /// @param scalar Scalar to do modulo with
    /// @return New matrix that represent modulo result
    SquareMat operator%(SquareMat mat, const int scalar);
    
    /// @brief Return the result of division matrix by scalar, by divide each cell by given scalar
    /// @param mat Matrix to divide
    /// @param scalar Scalar to do divide the matrix
    /// @return New matrix that represent division result
    SquareMat operator/(SquareMat mat, const double scalar);
    
    /// @brief Return matrix transpose
    /// @param mat Matrix to make transpose
    /// @return New matrix that represent origin matrix transpose
    SquareMat operator~(SquareMat mat);
    
    /// @brief Create and concatenate string that represent matrices to given output stream,
    /// mainly in order to print it
    /// @param stream Stream to concatenate string to it
    /// @param mat Matrix to print
    /// @return The given stream output, for enable concatenate to it
    ostream& operator<<(ostream& stream, const SquareMat& mat);
}
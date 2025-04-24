#include <cstddef>

namespace Matrix{
    class SquareMat{
        private:
            size_t rows, cols;
            double** mat;

            void allocateMem();
            void freeMem();
            void copyMem(const SquareMat&);

        public:
            SquareMat(size_t rows, size_t cols);

            SquareMat(const SquareMat &other) : SquareMat(other.rows, other.cols){
                this->copyMem(other);
            }

            ~SquareMat(){ this->freeMem();}

            SquareMat& operator=(const SquareMat& other);
            double* operator[](size_t) const ;

            SquareMat operator-() const;
            SquareMat operator+(const SquareMat&) const;
            SquareMat operator*(const SquareMat&) const;
            SquareMat operator%(const SquareMat&) const;
            SquareMat operator%(int) const;
            SquareMat operator/(int) const;
            SquareMat operator^(size_t) const;
            SquareMat operator~() const;
            double operator!() const;

            SquareMat& operator-=(const SquareMat&);
            SquareMat& operator+=(const SquareMat&);
            SquareMat& operator++();
            SquareMat& operator++(int);
            SquareMat& operator--();
            SquareMat& operator--(int);
            SquareMat& operator*=(const SquareMat&);
            SquareMat& operator*=(double);
            SquareMat& operator%=(const SquareMat&);
            SquareMat& operator%=(int);
            
            bool operator==(const SquareMat&) const;
            bool operator!=(const SquareMat&) const;
            bool operator<(const SquareMat&) const;
            bool operator<=(const SquareMat&) const;
            bool operator>(const SquareMat&) const;
            bool operator>=(const SquareMat&) const;
    };
}
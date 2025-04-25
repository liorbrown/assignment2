#include <cstddef>
#include <iostream>

using namespace std;

namespace Matrix{
    class SquareMat{
        private:
            size_t size;
            double** mat;

            void allocateMem();
            void freeMem();
            void copyMem(const SquareMat&);
            double getSum() const;
            SquareMat* getMinor(const size_t col) const;
            
        public:
            SquareMat(size_t);
            SquareMat(const SquareMat& other): SquareMat(other.size) {this->copyMem(other);}
            SquareMat& operator=(const SquareMat& other);
            ~SquareMat(){ this->freeMem();}            

            double* operator[](size_t row) const {return this->mat[row];}

            SquareMat& operator-=(const SquareMat&);
            SquareMat& operator+=(const SquareMat&);
            SquareMat& operator++();
            SquareMat operator++(int);
            SquareMat& operator--();
            SquareMat operator--(int);
            
            SquareMat& operator*=(const SquareMat&);
            SquareMat& operator*=(const double);
            SquareMat& operator/=(const double);
            SquareMat& operator%=(const SquareMat&);
            SquareMat& operator%=(const int);
            
            bool operator==(const SquareMat&) const;
            bool operator!=(const SquareMat&) const;
            bool operator<(const SquareMat&) const;
            bool operator<=(const SquareMat&) const;
            bool operator>(const SquareMat&) const;
            bool operator>=(const SquareMat&) const;

            SquareMat operator-() const;
            SquareMat operator^(const size_t exp);
            double operator!() const;

            friend ostream& operator<<(ostream&, const SquareMat&);
            friend SquareMat operator~(SquareMat mat);        
    };

    SquareMat operator-(SquareMat left, const SquareMat& right);
    SquareMat operator+(SquareMat left, const SquareMat& right);
    SquareMat operator*(SquareMat left, const SquareMat& right);        
    SquareMat operator*(SquareMat mat, const double scalar);        
    SquareMat operator*(const double scalar,const SquareMat& mat);        
    SquareMat operator%(SquareMat left, const SquareMat& right);        
    SquareMat operator%(SquareMat mat, const int scalar);        
    SquareMat operator/(SquareMat mat, const double scalar);        
    SquareMat operator~(SquareMat mat);
}
#include <cstddef>

namespace Matrix{
    class SquareMat{
        private:
            size_t size;
            double** mat;

            void allocateMem();
            void freeMem();
            void copyMem(const SquareMat&);
            double getSum() const;
            SquareMat getIdentityMat() const;
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
            double operator!() const;

            friend ostream& operator<<(ostream&, const SquareMat&);
            friend SquareMat operator^(SquareMat mat, const size_t exp);
            friend SquareMat operator~(SquareMat mat);
    };
}
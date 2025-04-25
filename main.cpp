#include <stdlib.h>

#include "SquareMat.hpp"

using namespace Matrix;

int main(){
    const size_t SIZE = 5;
    SquareMat mat{SIZE};
    
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            mat[i][j] =  (rand() % 69) / 7.0;
    
    SquareMat copyMat{mat};
    SquareMat assignMat{SIZE};
    assignMat = mat;
    
    cout << "mat :" << mat << endl 
         << "copyMat :" <<  copyMat << endl 
         << "assignMat :" << assignMat;
    
    cout << " Is equal : " << (mat == copyMat) << endl;
    cout << " Is not equal : " << (mat != copyMat) << endl;
    cout << " Is greater than : " << (mat > copyMat) << endl;
    cout << " Is greater or equal than : " << (mat >= copyMat) << endl;
    cout << " Is smaller than : " << (mat < copyMat) << endl;
    cout << " Is smaller or equal than : " << (mat <= copyMat) << endl;
    
    cout << "mat + copyMat : " << (mat + copyMat);
    cout << "mat - copyMat : " << (mat - copyMat);
    cout << "mat % copyMat : " << (mat % copyMat);
    cout << "mat * copyMat : " << (mat * copyMat);
    
    cout << "mat ^ 2 : " << (mat ^ 2);
    cout << "mat ^ 1 : " << (mat ^ 1);
    cout << "mat ^ 0 : " << (mat ^ 0);
    cout << "mat * 0.76 : " << (mat * 0.76);
    cout << "0.76 * mat : " << (0.76 * mat);
    cout << "mat / (1 / 0.76) : " << (mat / (1 / 0.76));
    cout << "mat % 2.54 : " << (mat % 2.54);
    
    
    cout << "-mat: " << (-mat);
    cout << "|mat| : " << (!mat) << endl;
    cout << "mat transpose : " << (~mat);

    assignMat += copyMat;
    cout << "mat after += copyMat : " << assignMat;

    assignMat = mat;
    assignMat -= copyMat;

    cout << "mat after -= copyMat : " << assignMat;

    assignMat = mat;
    assignMat %= copyMat;

    cout << "mat after %= copyMat : " << assignMat;

    assignMat = mat;
    assignMat *= copyMat;

    cout << "mat after *= copyMat : " << assignMat;

    assignMat = mat;
    assignMat *= 0.84;

    cout << "mat after *= 0.84 : " << assignMat;

    assignMat = mat;
    assignMat /= (1 / 0.84);

    cout << "mat after /= (1 / 0.84) : " << assignMat;

    assignMat = mat;
    assignMat %= 3.45;

    cout << "mat after %= 3.45 : " << assignMat;

    assignMat = mat;
    assignMat++;

    cout << "mat after mat++ : " << assignMat;

    assignMat = mat;
    ++assignMat;

    cout << "mat after ++mat : " << assignMat;

    assignMat = mat;
    assignMat--;

    cout << "mat after mat-- : " << assignMat;

    assignMat = mat;
    --assignMat;

    cout << "mat after --mat : " << assignMat;
}
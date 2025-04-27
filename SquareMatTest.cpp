// liorbrown@outlook.co.il

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.hpp"
#include "SquareMat.hpp"

#define DEFAULT_SIZE (3)
#define PRECISION (0.0001)

using namespace Matrix;

SquareMat* globalMat1;
SquareMat* globalMat2;
SquareMat* zeroMat;
SquareMat* identityMat;

bool isEqual(const double d1, const double d2)
{
    return (abs(d1 - d2) < PRECISION);
}

bool isEqual(const SquareMat& mat1, const SquareMat& mat2)
{
    if (mat1.getSize() != mat2.getSize())
        return false;
    
    for (size_t i = 0; i < mat1.getSize(); i++)
        for (size_t j = 0; j < mat1.getSize(); j++)
            if (!isEqual(mat1[i][j], mat2[i][j]))
                return false;                

    return true;
}

TEST_CASE("Creating matrix")
{
    CHECK_THROWS_AS(SquareMat{0}, invalid_argument);

    globalMat1 = new SquareMat(DEFAULT_SIZE);
    zeroMat = new SquareMat{DEFAULT_SIZE};
    identityMat = new SquareMat{DEFAULT_SIZE};

    for (size_t i = 0; i < DEFAULT_SIZE; i++)
    {
        (*identityMat)[i][i] = 1.0;

        for (size_t j = 0; j < DEFAULT_SIZE; j++)
            (*zeroMat)[i][j] = 0.0;
    }

    CHECK(isEqual(*zeroMat, *globalMat1));
        
    (*globalMat1)[0][0] = 4.5;
    (*globalMat1)[0][1] = 8.0;
    (*globalMat1)[0][2] = 7.0;
    (*globalMat1)[1][0] = 2.0;
    (*globalMat1)[1][1] = 0.0;
    (*globalMat1)[1][2] = -12.0;
    (*globalMat1)[2][0] = 3.3;
    (*globalMat1)[2][1] = 5.6;
    (*globalMat1)[2][2] = -2.1;

    globalMat2 = new SquareMat{DEFAULT_SIZE};

    (*globalMat2)[0][0] = 6.7;
    (*globalMat2)[0][1] = 3.2;
    (*globalMat2)[0][2] = 50;
    (*globalMat2)[1][0] = -6.6;
    (*globalMat2)[1][1] = 19;
    (*globalMat2)[1][2] = -87;
    (*globalMat2)[2][0] = 6.1;
    (*globalMat2)[2][1] = -8.8;
    (*globalMat2)[2][2] = 4;
}

TEST_CASE("Copy constructor and assignment operator")
{
    SquareMat matCopy{*globalMat1};

    CHECK (isEqual(matCopy, *globalMat1));

    SquareMat matAssignment{8};
    matAssignment = *globalMat1;

    CHECK (isEqual(matAssignment, *globalMat1));

    matAssignment[1][2] = 70;
    matAssignment = *globalMat1;

    CHECK (isEqual(matAssignment, *globalMat1));
}

TEST_CASE("Equality operators")
{
    SquareMat mat{*globalMat1};

    CHECK(mat == *globalMat1);
    CHECK(mat >= *globalMat1);
    CHECK(mat <= *globalMat1);
    CHECK_FALSE(mat != *globalMat1);
    CHECK_FALSE(mat < *globalMat1);
    CHECK_FALSE(mat > *globalMat1);

    mat[1][2] += 5.5;
    mat[0][2] -= 5.5;

    CHECK(mat == *globalMat1);
    CHECK(mat >= *globalMat1);
    CHECK(mat <= *globalMat1);
    CHECK_FALSE(mat != *globalMat1);
    CHECK_FALSE(mat < *globalMat1);
    CHECK_FALSE(mat > *globalMat1);

    mat[0][1] += 3;

    CHECK_FALSE(mat == *globalMat1);
    CHECK(mat >= *globalMat1);
    CHECK_FALSE(mat <= *globalMat1);
    CHECK(mat != *globalMat1);
    CHECK_FALSE(mat < *globalMat1);
    CHECK(mat > *globalMat1);

    mat[0][1] -= 10;

    CHECK_FALSE(mat == *globalMat1);
    CHECK_FALSE(mat >= *globalMat1);
    CHECK(mat <= *globalMat1);
    CHECK(mat != *globalMat1);
    CHECK(mat < *globalMat1);
    CHECK_FALSE(mat > *globalMat1);
}

TEST_SUITE("Unary operators")
{
    TEST_CASE ("Determinant")
    {
        SquareMat mat{5};
        CHECK_FALSE(!mat);

        mat = *globalMat1;
        double expected = 97.6;

        CHECK(isEqual(expected, !mat));

        mat[0][1] = 0;
        expected = 380.8;

        CHECK(isEqual(expected, !mat));

        mat[0][0] = mat[0][2] = 0;

        CHECK_FALSE(!mat);

        mat = *globalMat1;
        mat[2][0] = mat[2][1] = mat[2][2] = 0;

        CHECK_FALSE(!mat);

        mat = *globalMat1;
        mat[0][1] = mat[1][1] = mat[2][1] = 0;

        CHECK_FALSE(!mat);
    }

    TEST_CASE("Minus")
    {
        SquareMat mat{4};
        CHECK(isEqual(mat, -mat));

        mat = *globalMat1;

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = -4.5;
        expected[0][1] = -8.0;
        expected[0][2] = -7.0;
        expected[1][0] = -2.0;
        expected[1][1] = 0.0;
        expected[1][2] = 12.0;
        expected[2][0] = -3.3;
        expected[2][1] = -5.6;
        expected[2][2] = 2.1;

        CHECK(isEqual(expected, -mat));

        CHECK(isEqual(*globalMat1, mat));
    }

    TEST_CASE("Transpose")
    {
        SquareMat mat{4};
        CHECK(isEqual(mat, ~mat));

        mat = *globalMat1;

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 4.5;
        expected[0][1] = 2.0;
        expected[0][2] = 3.3;
        expected[1][0] = 8.0;
        expected[1][1] = 0.0;
        expected[1][2] = 5.6;
        expected[2][0] = 7.0;
        expected[2][1] = -12.0;
        expected[2][2] = -2.1;

        CHECK(isEqual(expected, ~mat));

        CHECK(isEqual(*globalMat1, mat));
    }
}

TEST_SUITE("Scalar operators")
{
    TEST_CASE("Power")
    {
        SquareMat mat{DEFAULT_SIZE};

        CHECK(isEqual(*identityMat, mat ^ 0));
        CHECK(isEqual(*zeroMat, mat ^ 1));
        CHECK(isEqual(*zeroMat, mat ^ 2));
        CHECK(isEqual(*zeroMat, mat ^ 10));

        mat = *globalMat1;

        CHECK(isEqual(*identityMat, mat ^ 0));
        CHECK(isEqual(mat, mat ^ 1));

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 59.35;
        expected[0][1] = 75.2;
        expected[0][2] = -79.2;
        expected[1][0] = -30.6;
        expected[1][1] = -51.2;
        expected[1][2] = 39.2;
        expected[2][0] = 19.12;
        expected[2][1] = 14.64;
        expected[2][2] = -39.69;

        CHECK(isEqual(expected, mat ^ 2));

        expected[0][0] = 156.115;
        expected[0][1] = 31.28;
        expected[0][2] = -320.63;
        expected[1][0] = -110.74;
        expected[1][1] = -25.28;
        expected[1][2] = 317.88;
        expected[2][0] = -15.657;
        expected[2][1] = -69.304;
        expected[2][2] = 41.509;

        CHECK(isEqual(expected, mat ^ 3));

        CHECK(isEqual(*globalMat1, mat));

        CHECK(isEqual(*identityMat, (*identityMat) ^ 5));
    }

    TEST_CASE("Scalar Multiply")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        CHECK(isEqual(*zeroMat, mat * 0));
        CHECK(isEqual(*zeroMat, 0 * mat));
        CHECK(isEqual(*zeroMat, mat * 1));
        CHECK(isEqual(*zeroMat, 1 * mat));
        CHECK(isEqual(*zeroMat, mat * 4.6));
        CHECK(isEqual(*zeroMat, 4.6 * mat));

        mat = *globalMat1;

        CHECK(isEqual(*zeroMat, mat * 0));
        CHECK(isEqual(*zeroMat, 0 * mat));
        CHECK(isEqual(mat, mat * 1));
        CHECK(isEqual(mat, 1 * mat));

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 15.75;
        expected[0][1] = 28;
        expected[0][2] = 24.5;
        expected[1][0] = 7;
        expected[1][1] = 0;
        expected[1][2] = -42;
        expected[2][0] = 11.55;
        expected[2][1] = 19.6;
        expected[2][2] = -7.35;

        CHECK(isEqual(expected, mat * 3.5));
        CHECK(isEqual(expected, 3.5 * mat));

        CHECK(isEqual(*globalMat1, mat));
    }

    TEST_CASE("Scalar division")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        CHECK(isEqual(*zeroMat, mat / 1));
        CHECK(isEqual(*zeroMat, mat / 4.6));

        mat = *globalMat1;

        CHECK_THROWS_AS(mat / 0, invalid_argument);

        CHECK(isEqual(mat, mat / 1));

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 15.75;
        expected[0][1] = 28;
        expected[0][2] = 24.5;
        expected[1][0] = 7;
        expected[1][1] = 0;
        expected[1][2] = -42;
        expected[2][0] = 11.55;
        expected[2][1] = 19.6;
        expected[2][2] = -7.35;

        CHECK(isEqual(expected, mat / (1 / 3.5)));
        
        CHECK(isEqual(*globalMat1, mat));
    }

    TEST_CASE("Scalar modulo")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        CHECK(isEqual(*zeroMat, mat % 1));
        CHECK(isEqual(*zeroMat, mat % 4.6));

        mat = *globalMat1;

        CHECK_THROWS_AS(mat % 0, invalid_argument);

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 1.5;
        expected[0][1] = 2;
        expected[0][2] = 1;
        expected[1][0] = 2;
        expected[1][1] = 0;
        expected[1][2] = 0;
        expected[2][0] = 0.3;
        expected[2][1] = 2.6;
        expected[2][2] = -2.1;

        CHECK(isEqual(expected, mat % 3));
        
        CHECK(isEqual(*globalMat1, mat));
    }
}

TEST_SUITE("2 Matrices operators")
{
    TEST_CASE("+ operator")
    {
        SquareMat mat1{5};

        CHECK_THROWS_AS(mat1 + *globalMat1, invalid_argument);

        CHECK(isEqual(*zeroMat, *zeroMat + *zeroMat));

        mat1 = *globalMat1;

        CHECK(isEqual(mat1, mat1 + *zeroMat));

        

        SquareMat mat2 = *globalMat2;
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 11.2;
        expected[0][1] = 11.2;
        expected[0][2] = 57;
        expected[1][0] = -4.6;
        expected[1][1] = 19;
        expected[1][2] = -99;
        expected[2][0] = 9.4;
        expected[2][1] = -3.2;
        expected[2][2] = 1.9;

        CHECK(isEqual(expected, mat1 + mat2));
        CHECK(isEqual(expected, mat2 + mat1));

        CHECK(isEqual(*globalMat1, mat1));
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("Multiply(%) operator")
    {
        SquareMat mat1{5};

        CHECK_THROWS_AS(mat1 % *globalMat1, invalid_argument);

        CHECK(isEqual(*zeroMat, *zeroMat % *zeroMat));

        mat1 = *globalMat1;

        CHECK(isEqual(*zeroMat, mat1 % *zeroMat));
        CHECK(isEqual(*zeroMat, *zeroMat % mat1));

        SquareMat mat2 = *globalMat2;
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 30.15;
        expected[0][1] = 25.6;
        expected[0][2] = 350;
        expected[1][0] = -13.2;
        expected[1][1] = 0;
        expected[1][2] = 1044;
        expected[2][0] = 20.13;
        expected[2][1] = -49.28;
        expected[2][2] = -8.4;

        CHECK(isEqual(expected, mat1 % mat2));
        CHECK(isEqual(expected, mat2 % mat1));

        CHECK(isEqual(*globalMat1, mat1));
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("- operator")
    {
        SquareMat mat1{5};

        CHECK_THROWS_AS(mat1 - *globalMat1, invalid_argument);

        CHECK(isEqual(*zeroMat, *zeroMat - *zeroMat));

        mat1 = *globalMat1;

        CHECK(isEqual(mat1, mat1 - *zeroMat));

        SquareMat mat2 = *globalMat2;
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = -2.2;
        expected[0][1] = 4.8;
        expected[0][2] = -43;
        expected[1][0] = 8.6;
        expected[1][1] = -19;
        expected[1][2] = 75;
        expected[2][0] = -2.8;
        expected[2][1] = 14.4;
        expected[2][2] = -6.1;

        CHECK(isEqual(expected, mat1 - mat2));

        CHECK(isEqual(*globalMat1, mat1));
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("Matrices multiplication")
    {
        SquareMat mat1{5};

        CHECK_THROWS_AS(mat1 * *globalMat1, invalid_argument);

        CHECK(isEqual(*zeroMat, *zeroMat * *zeroMat));

        mat1 = *globalMat1;

        CHECK(isEqual(*zeroMat, mat1 * *zeroMat));
        CHECK(isEqual(*zeroMat, *zeroMat * mat1));

        CHECK(isEqual(mat1, mat1 * *identityMat));
        CHECK(isEqual(mat1, *identityMat * mat1));

        SquareMat mat2 = *globalMat2;
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 20.05;
        expected[0][1] = 104.8;
        expected[0][2] = -443;
        expected[1][0] = -59.8;
        expected[1][1] = 112;
        expected[1][2] = 52;
        expected[2][0] = -27.66;
        expected[2][1] = 135.44;
        expected[2][2] = -330.6;

        CHECK(isEqual(expected, mat1 * mat2));

        CHECK(isEqual(*globalMat1, mat1));
        CHECK(isEqual(*globalMat2, mat2));
    }
}

TEST_SUITE("Self assignment operators")
{
    TEST_CASE("Scalar Multiply")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        CHECK(isEqual(*zeroMat, mat *= 0));
        CHECK(isEqual(*zeroMat, mat));
        CHECK(isEqual(*zeroMat, mat *= 1));
        CHECK(isEqual(*zeroMat, mat));
        CHECK(isEqual(*zeroMat, mat *= 4.6));
        CHECK(isEqual(*zeroMat, mat));

        mat = *globalMat1;

        CHECK(isEqual(*globalMat1, mat *= 1));
        CHECK(isEqual(*globalMat1, mat));

        CHECK(isEqual(*zeroMat, mat *= 0));
        CHECK(isEqual(*zeroMat, mat));
        
        mat = *globalMat1;

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 15.75;
        expected[0][1] = 28;
        expected[0][2] = 24.5;
        expected[1][0] = 7;
        expected[1][1] = 0;
        expected[1][2] = -42;
        expected[2][0] = 11.55;
        expected[2][1] = 19.6;
        expected[2][2] = -7.35;

        CHECK(isEqual(expected, mat *= 3.5));
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("Scalar division")
    {
        SquareMat mat{DEFAULT_SIZE};

        CHECK_THROWS_AS(mat /= 0, invalid_argument);
        
        CHECK(isEqual(*zeroMat, mat /= 4.6));
        CHECK(isEqual(*zeroMat, mat));

        mat = *globalMat1;        

        CHECK(isEqual(*globalMat1, mat /= 1));

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 15.75;
        expected[0][1] = 28;
        expected[0][2] = 24.5;
        expected[1][0] = 7;
        expected[1][1] = 0;
        expected[1][2] = -42;
        expected[2][0] = 11.55;
        expected[2][1] = 19.6;
        expected[2][2] = -7.35;

        CHECK(isEqual(expected, mat /= (1 / 3.5)));
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("Scalar modulo")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        CHECK_THROWS_AS(mat %= 0, invalid_argument);
    
        CHECK(isEqual(*zeroMat, mat %= 1));
        CHECK(isEqual(*zeroMat, mat));

        mat = *globalMat1;
        
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 1.5;
        expected[0][1] = 2;
        expected[0][2] = 1;
        expected[1][0] = 2;
        expected[1][1] = 0;
        expected[1][2] = 0;
        expected[2][0] = 0.3;
        expected[2][1] = 2.6;
        expected[2][2] = -2.1;

        CHECK(isEqual(expected, mat %= 3.5));
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("++mat operator")
    {
        SquareMat mat{*globalMat1};

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 5.5;
        expected[0][1] = 9;
        expected[0][2] = 8;
        expected[1][0] = 3;
        expected[1][1] = 1;
        expected[1][2] = -11;
        expected[2][0] = 4.3;
        expected[2][1] = 6.6;
        expected[2][2] = -1.1;

        CHECK(isEqual(expected, ++mat));
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("mat++ operator")
    {
        SquareMat mat{*globalMat1};

        CHECK(isEqual(*globalMat1, mat++));

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 5.5;
        expected[0][1] = 9;
        expected[0][2] = 8;
        expected[1][0] = 3;
        expected[1][1] = 1;
        expected[1][2] = -11;
        expected[2][0] = 4.3;
        expected[2][1] = 6.6;
        expected[2][2] = -1.1;
        
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("--mat operator")
    {
        SquareMat mat{*globalMat1};

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 3.5;
        expected[0][1] = 7;
        expected[0][2] = 6;
        expected[1][0] = 1;
        expected[1][1] = -1;
        expected[1][2] = -13;
        expected[2][0] = 2.3;
        expected[2][1] = 4.6;
        expected[2][2] = -3.1;

        CHECK(isEqual(expected, --mat));
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("mat-- operator")
    {
        SquareMat mat{*globalMat1};

        CHECK(isEqual(*globalMat1, mat--));

        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 3.5;
        expected[0][1] = 7;
        expected[0][2] = 6;
        expected[1][0] = 1;
        expected[1][1] = -1;
        expected[1][2] = -13;
        expected[2][0] = 2.3;
        expected[2][1] = 4.6;
        expected[2][2] = -3.1;
        
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("+= operator")
    {
        SquareMat mat1{5};

        CHECK_THROWS_AS(mat1 += *globalMat1, invalid_argument);

        mat1 = *zeroMat;

        CHECK(isEqual(*zeroMat, mat1 += mat1));

        mat1 = *globalMat1;

        CHECK(isEqual(*globalMat1, mat1 += *zeroMat));
        CHECK(isEqual(*globalMat1, mat1));

        SquareMat mat2 = *globalMat2;
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 11.2;
        expected[0][1] = 11.2;
        expected[0][2] = 57;
        expected[1][0] = -4.6;
        expected[1][1] = 19;
        expected[1][2] = -99;
        expected[2][0] = 9.4;
        expected[2][1] = -3.2;
        expected[2][2] = 1.9;

        CHECK(isEqual(expected, mat1 += mat2));
        CHECK(isEqual(expected, mat1));

        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("Multiply(%) operator")
    {
        SquareMat mat1{5};

        CHECK_THROWS_AS(mat1 %= *globalMat1, invalid_argument);

        mat1 = *globalMat1;

        mat1 %= *zeroMat;

        CHECK(isEqual(*zeroMat, mat1 % mat1));

        mat1 = *globalMat1;

        CHECK(isEqual(*zeroMat, mat1 %= *zeroMat));
        CHECK(isEqual(*zeroMat, mat1));

        mat1 = *globalMat1;
        SquareMat mat2 = *globalMat2;
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 30.15;
        expected[0][1] = 25.6;
        expected[0][2] = 350;
        expected[1][0] = -13.2;
        expected[1][1] = 0;
        expected[1][2] = 1044;
        expected[2][0] = 20.13;
        expected[2][1] = -49.28;
        expected[2][2] = -8.4;

        CHECK(isEqual(expected, mat1 %= mat2));
        CHECK(isEqual(expected, mat1));

        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("- operator")
    {
        SquareMat mat1{5};

        CHECK_THROWS_AS(mat1 -= *globalMat1, invalid_argument);

        mat1 = *zeroMat;

        CHECK(isEqual(*zeroMat, mat1 -= mat1));

        mat1 = *globalMat1;

        CHECK(isEqual(*globalMat1, mat1 -= *zeroMat));
        CHECK(isEqual(*globalMat1, mat1));

        SquareMat mat2 = *globalMat2;
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = -2.2;
        expected[0][1] = 4.8;
        expected[0][2] = -43;
        expected[1][0] = 8.6;
        expected[1][1] = -19;
        expected[1][2] = 75;
        expected[2][0] = -2.8;
        expected[2][1] = 14.4;
        expected[2][2] = -6.1;

        CHECK(isEqual(expected, mat1 -= mat2));
        CHECK(isEqual(expected, mat1));

        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("Matrices multiplication")
    {
        SquareMat mat1{5};

        CHECK_THROWS_AS(mat1 *= *globalMat1, invalid_argument);

        mat1 = *zeroMat;

        CHECK(isEqual(*zeroMat, mat1 *= mat1));

        mat1 = *globalMat1;

        CHECK(isEqual(*zeroMat, mat1 *= *zeroMat));
        CHECK(isEqual(*zeroMat, mat1));

        mat1 = *globalMat1;

        CHECK(isEqual(*globalMat1, mat1 * *identityMat));
        CHECK(isEqual(*globalMat1, *identityMat * mat1));

        SquareMat mat2 = *globalMat2;
        SquareMat expected{DEFAULT_SIZE};

        expected[0][0] = 20.05;
        expected[0][1] = 104.8;
        expected[0][2] = -443;
        expected[1][0] = -59.8;
        expected[1][1] = 112;
        expected[1][2] = 52;
        expected[2][0] = -27.66;
        expected[2][1] = 135.44;
        expected[2][2] = -330.6;

        CHECK(isEqual(expected, mat1 *= mat2));
        CHECK(isEqual(expected, mat1));

        CHECK(isEqual(*globalMat2, mat2));
    }
}

TEST_CASE("Free matrices")
{
    if (globalMat1)
        delete globalMat1;

    if (zeroMat)
        delete zeroMat;

    if (identityMat)
        delete identityMat;

    if (globalMat2)
        delete globalMat2;
}
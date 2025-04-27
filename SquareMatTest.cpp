// liorbrown@outlook.co.il

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.hpp"
#include "SquareMat.hpp"

#define DEFAULT_SIZE (3)
#define EPS (0.0001)

using namespace Matrix;

SquareMat* globalMat1;
SquareMat* globalMat2;
SquareMat* zeroMat;
SquareMat* identityMat;

/// @brief Checks whether two numbers are close to each other up to epsilon.
/// @param d1 First number to check
/// @param d2 Seconed number to check
/// @return True - if they close enough, False - Otherwise
bool isEqual(const double d1, const double d2)
{
    return (abs(d1 - d2) < EPS);
}

/// @brief Check if 2 matrices are identical (up to epsilon)
/// @param mat1 First matrix to equal
/// @param mat2 Seconed matrix to equal
/// @return True - if they are identical, False - otherwise
bool isEqual(const SquareMat& mat1, const SquareMat& mat2)
{
    if (mat1.getSize() != mat2.getSize())
        return false;
    
    // Runs on each cell and check if cells value are differ
    for (size_t i = 0; i < mat1.getSize(); i++)
        for (size_t j = 0; j < mat1.getSize(); j++)
            if (!isEqual(mat1[i][j], mat2[i][j]))
                return false;                

    // If allthe cell equals returns true
    return true;
}

TEST_CASE("Creating matrix")
{
    // Ensure canwt create matrix in size of 0
    CHECK_THROWS_AS(SquareMat{0}, invalid_argument);

    globalMat1 = new SquareMat(DEFAULT_SIZE);
    zeroMat = new SquareMat{DEFAULT_SIZE};
    identityMat = new SquareMat{DEFAULT_SIZE};

    // Initialize identity and zero matrices
    for (size_t i = 0; i < DEFAULT_SIZE; i++)
    {
        (*identityMat)[i][i] = 1.0;

        for (size_t j = 0; j < DEFAULT_SIZE; j++)
            (*zeroMat)[i][j] = 0.0;
    }

    // Check if new matrices initialize to zero matrix
    CHECK(isEqual(*zeroMat, *globalMat1));

    // Initialize globalMat1 & globalMat2 with arbitary values for next testing,
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
    // Check copy constructor
    SquareMat matCopy{*globalMat1};

    CHECK (isEqual(matCopy, *globalMat1));

    SquareMat matAssignment{8};

    // Check assignment operator where matrices size are differ (Make re-allocation)
    matAssignment = *globalMat1;

    CHECK (isEqual(matAssignment, *globalMat1));

    matAssignment[1][2] = 70;

    // Check assignment operator where matrices size are equal (Not make re-allocation)
    matAssignment = *globalMat1;

    CHECK (isEqual(matAssignment, *globalMat1));
}

TEST_CASE("Equality operators")
{
    // Checking identical matrices
    SquareMat mat{*globalMat1};

    CHECK(mat == *globalMat1);
    CHECK(mat >= *globalMat1);
    CHECK(mat <= *globalMat1);
    CHECK_FALSE(mat != *globalMat1);
    CHECK_FALSE(mat < *globalMat1);
    CHECK_FALSE(mat > *globalMat1);

    // Checking different matrices, but with same sum
    mat[1][2] += 5.5;
    mat[0][2] -= 5.5;

    CHECK(mat == *globalMat1);
    CHECK(mat >= *globalMat1);
    CHECK(mat <= *globalMat1);
    CHECK_FALSE(mat != *globalMat1);
    CHECK_FALSE(mat < *globalMat1);
    CHECK_FALSE(mat > *globalMat1);

    // Checking when first matrix is greater
    mat[0][1] += 3;

    CHECK_FALSE(mat == *globalMat1);
    CHECK(mat >= *globalMat1);
    CHECK_FALSE(mat <= *globalMat1);
    CHECK(mat != *globalMat1);
    CHECK_FALSE(mat < *globalMat1);
    CHECK(mat > *globalMat1);

    // Checking when first matrix is smaller
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
        // Check determinent of zero matrix
        SquareMat mat{5};
        CHECK_FALSE(!mat);

        // Check determinent when first row not contain 0
        mat = *globalMat1;
        double expected = 97.6;

        CHECK(isEqual(expected, !mat));

        // Check determinent when first row contain 0
        mat[0][1] = 0;
        expected = 380.8;

        CHECK(isEqual(expected, !mat));

        // Check determinent when first row is all 0
        mat[0][0] = mat[0][2] = 0;

        CHECK_FALSE(!mat);

        // Check determinent when other row is all 0
        mat = *globalMat1;
        mat[2][0] = mat[2][1] = mat[2][2] = 0;

        CHECK_FALSE(!mat);

        // Check determinent when one column is all 0
        mat = *globalMat1;
        mat[0][1] = mat[1][1] = mat[2][1] = 0;

        CHECK_FALSE(!mat);
    }

    TEST_CASE("Minus")
    {
        // Check minus of zero matrix
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

        // Ensure that origin matrix not changed by operator
        CHECK(isEqual(*globalMat1, mat));
    }

    TEST_CASE("Transpose")
    {
        // Check transpose of zero matrix
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

        // Ensure that origin matrix not changed by operator
        CHECK(isEqual(*globalMat1, mat));
    }
}

TEST_SUITE("Scalar operators")
{
    TEST_CASE("Power")
    {
        SquareMat mat{DEFAULT_SIZE};

        // Check that zero matrix power 0 is identity matrix
        CHECK(isEqual(*identityMat, mat ^ 0));

        // Check zero matrix other powers are zero matrix
        CHECK(isEqual(*zeroMat, mat ^ 1));
        CHECK(isEqual(*zeroMat, mat ^ 2));
        CHECK(isEqual(*zeroMat, mat ^ 10));

        mat = *globalMat1;

        // Check that matrix power 0 is identity matrix
        CHECK(isEqual(*identityMat, mat ^ 0));

        // Check that matrix power 1 is equal to matrix
        CHECK(isEqual(*globalMat1, mat ^ 1));

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

        // Ensure that origin matrix not changed by operator
        CHECK(isEqual(*globalMat1, mat));

        // Check that identity matrix in any power is identity matrix
        CHECK(isEqual(*identityMat, (*identityMat) ^ 0));
        CHECK(isEqual(*identityMat, (*identityMat) ^ 1));
        CHECK(isEqual(*identityMat, (*identityMat) ^ 4));
    }

    TEST_CASE("Scalar Multiply")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        // Check zero matrix muliply by any is zero matrix
        CHECK(isEqual(*zeroMat, mat * 0));
        CHECK(isEqual(*zeroMat, 0 * mat));
        CHECK(isEqual(*zeroMat, mat * 1));
        CHECK(isEqual(*zeroMat, 1 * mat));
        CHECK(isEqual(*zeroMat, mat * 4.6));
        CHECK(isEqual(*zeroMat, 4.6 * mat));

        mat = *globalMat1;

        // Check that multiply by zero give zero matrix
        CHECK(isEqual(*zeroMat, mat * 0));
        CHECK(isEqual(*zeroMat, 0 * mat));

        // Check that multiply by 1 give same matrix
        CHECK(isEqual(*globalMat1, mat * 1));
        CHECK(isEqual(*globalMat1, 1 * mat));

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

        // Ensure that origin matrix not changed by operator
        CHECK(isEqual(*globalMat1, mat));
    }

    TEST_CASE("Scalar division")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        // Check zero matrix divide by any is zero matrix
        CHECK(isEqual(*zeroMat, mat / 1));
        CHECK(isEqual(*zeroMat, mat / 4.6));

        mat = *globalMat1;

        // Check exception when try to divide by zero
        CHECK_THROWS_AS(mat / 0, invalid_argument);

        // Check divide by one
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

        // The using of opposite number from previous test case
        // spare me from additional calculation 😎
        CHECK(isEqual(expected, mat / (1 / 3.5)));
        
        // Ensure that origin matrix not changed by operator
        CHECK(isEqual(*globalMat1, mat));
    }

    TEST_CASE("Scalar modulo")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        // Check modulo of zero matrix
        CHECK(isEqual(*zeroMat, mat % 1));
        CHECK(isEqual(*zeroMat, mat % 4.6));

        mat = *globalMat1;

        // Ensure modulo by zero raise exception
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

        // Ensure that origin matrix not changed by operator
        CHECK(isEqual(*globalMat1, mat));
    }
}

TEST_SUITE("2 Matrices operators")
{
    TEST_CASE("+ operator")
    {
        SquareMat mat1{5};

        // Ensure operator on matrices with differ size raise exception
        CHECK_THROWS_AS(mat1 + *globalMat1, invalid_argument);

        CHECK(isEqual(*zeroMat, *zeroMat + *zeroMat));

        mat1 = *globalMat1;

        // Check that adding zero mat not change result
        CHECK(isEqual(*globalMat1, mat1 + *zeroMat));

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

        // Checking that operator is commutative as expected
        CHECK(isEqual(expected, mat1 + mat2));
        CHECK(isEqual(expected, mat2 + mat1));

        // Ensure that origin matrices not changed by operator
        CHECK(isEqual(*globalMat1, mat1));
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("Multiply(%) operator")
    {
        SquareMat mat1{5};

        // Ensure operator on matrices with differ size raise exception
        CHECK_THROWS_AS(mat1 % *globalMat1, invalid_argument);

        CHECK(isEqual(*zeroMat, *zeroMat % *zeroMat));

        mat1 = *globalMat1;

        // Check that multiply by zero matrix make zero matrix
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

        // Checking that operator is commutative as expected
        CHECK(isEqual(expected, mat1 % mat2));
        CHECK(isEqual(expected, mat2 % mat1));

        // Ensure that origin matrices not changed by operator
        CHECK(isEqual(*globalMat1, mat1));
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("(matrix - matrix) operator")
    {
        SquareMat mat1{5};

        // Ensure operator on matrices with differ size raise exception
        CHECK_THROWS_AS(mat1 - *globalMat1, invalid_argument);

        CHECK(isEqual(*zeroMat, *zeroMat - *zeroMat));

        mat1 = *globalMat1;

        // Check that adding zero mat not change result
        CHECK(isEqual(*globalMat1, mat1 - *zeroMat));

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

        // Checking that operator is not commutative as expected
        CHECK_FALSE(isEqual(expected, mat2 - mat1));

        // Ensure that origin matrices not changed by operator
        CHECK(isEqual(*globalMat1, mat1));
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("Matrices multiplication")
    {
        SquareMat mat1{5};

        // Ensure operator on matrices with differ size raise exception
        CHECK_THROWS_AS(mat1 * *globalMat1, invalid_argument);

        CHECK(isEqual(*zeroMat, *zeroMat * *zeroMat));

        mat1 = *globalMat1;

        // Check that multiply by zero matrix make zero matrix
        CHECK(isEqual(*zeroMat, mat1 * *zeroMat));
        CHECK(isEqual(*zeroMat, *zeroMat * mat1));

        // Check that multiply by identity matrix not change result
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

        // Checking that operator is not commutative as expected
        CHECK_FALSE(isEqual(expected, mat2 * mat1));

        // Ensure that origin matrices not changed by operator
        CHECK(isEqual(*globalMat1, mat1));
        CHECK(isEqual(*globalMat2, mat2));
    }
}

// In self assignment operators test suite every check divide to 2 checks:
// the first checks that the operator returns the operate return value,
// and the seconed ensure that the matrix changed permanently
TEST_SUITE("Self assignment operators")
{
    TEST_CASE("Scalar Multiply")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        // Check that multiplying zero matrix, gives zero matrix
        CHECK(isEqual(*zeroMat, mat *= 0));
        CHECK(isEqual(*zeroMat, mat));
        CHECK(isEqual(*zeroMat, mat *= 1));
        CHECK(isEqual(*zeroMat, mat));
        CHECK(isEqual(*zeroMat, mat *= 4.6));
        CHECK(isEqual(*zeroMat, mat));

        mat = *globalMat1;

        // Checks that muliply by 1 not change matrix
        CHECK(isEqual(*globalMat1, mat *= 1));
        CHECK(isEqual(*globalMat1, mat));

        // Check that multiplying by zero, gives zero matrix
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

        // Ensure that divide by zero raise exception
        CHECK_THROWS_AS(mat /= 0, invalid_argument);
        
        // Check duvude of zero matrix
        CHECK(isEqual(*zeroMat, mat /= 4.6));
        CHECK(isEqual(*zeroMat, mat));

        mat = *globalMat1;        

        // Check that divide by one make no change
        CHECK(isEqual(*globalMat1, mat /= 1));
        CHECK(isEqual(*globalMat1, mat));

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

        // The using of opposite number from previous test case
        // spare me from additional calculation 😎
        CHECK(isEqual(expected, mat /= (1 / 3.5)));
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("Scalar modulo")
    {
        SquareMat mat{DEFAULT_SIZE};
        
        // Check that modulo by zoer raise exception
        CHECK_THROWS_AS(mat %= 0, invalid_argument);
    
        // Check modulo on zero matrix
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

        // Check that ++mat returns value after changing
        CHECK(isEqual(expected, ++mat));
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("mat++ operator")
    {
        SquareMat mat{*globalMat1};

        // Check that mat++ return value before changing
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
        
        // Check that value changed
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

        // Check that ++mat returns value after changing
        CHECK(isEqual(expected, --mat));
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("mat-- operator")
    {
        SquareMat mat{*globalMat1};

        // Check that mat-- return value before changing
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
        
        // Check that value changed
        CHECK(isEqual(expected, mat));
    }

    TEST_CASE("+= operator")
    {
        SquareMat mat1{5};

        // Ensure operator on matrices with differ size raise exception
        CHECK_THROWS_AS(mat1 += *globalMat1, invalid_argument);

        mat1 = *zeroMat;

        CHECK(isEqual(*zeroMat, mat1 += mat1));

        mat1 = *globalMat1;

        // Check that adding zero matrix not change matrix
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

        // Ensure that seconed matrix not changed by operator
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("Multiply(%=) operator")
    {
        SquareMat mat1{5};

        // Ensure operator on matrices with differ size raise exception
        CHECK_THROWS_AS(mat1 %= *globalMat1, invalid_argument);

        mat1 = *globalMat1;

        // Check that multiply by zero give zero matrix
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

        // Ensure that seconed matrix not changed by operator
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("-= operator")
    {
        SquareMat mat1{5};

        // Ensure operator on matrices with differ size raise exception
        CHECK_THROWS_AS(mat1 -= *globalMat1, invalid_argument);

        mat1 = *zeroMat;

        CHECK(isEqual(*zeroMat, mat1 -= mat1));

        mat1 = *globalMat1;

        // Check that substruct zero matrix not change result
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

        // Ensure that seconed matrix not changed by operator
        CHECK(isEqual(*globalMat2, mat2));
    }

    TEST_CASE("Matrices multiplication")
    {
        SquareMat mat1{5};

        // Ensure operator on matrices with differ size raise exception
        CHECK_THROWS_AS(mat1 *= *globalMat1, invalid_argument);

        mat1 = *zeroMat;

        CHECK(isEqual(*zeroMat, mat1 *= mat1));

        mat1 = *globalMat1;

        // Check that multiplying by zero matrix give zero matrix
        CHECK(isEqual(*zeroMat, mat1 *= *zeroMat));
        CHECK(isEqual(*zeroMat, mat1));

        mat1 = *globalMat1;

        // Check that multiply by identity matrix, dont change matrix
        CHECK(isEqual(*globalMat1, mat1 *= *identityMat));
        CHECK(isEqual(*globalMat1, mat1));

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

        // Ensure that seconed matrix not changed by operator
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
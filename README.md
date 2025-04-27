This project was carried out as part of a bachelor's degree in computer and software engineering at Ariel University. The goal of the project is to practice c++ operator overloading.

In this project I implement square matrix class, and provide the following operators:

Unary operators:
- Minus matrix (-mat)
- Determinant (!mat)
- Transpose matrix (~mat)

Scalar operators:
- Muliplication (mat * scalar and scalar * mat)
- Division (mat / scalar)
- Modulo (mat % scalar)
- Power (mat ^ scalar)

2 matrices operators:
- Summarize (mat1 + mat2)
- Subtraction (mat1 - mat2)
- Matrix multiplication (mat1 * mat2)
- Elements multiplication (mat1 % mat2)

Self assignment operators:
- mat1 += mat2
- mat1 -= mat2
- mat1 *= mat2
- mat1 *= scalar
- mat1 %= mat2
- mat1 %= scalar
- mat++ (post-increment)
- ++mat (pre-increment)
- mat-- (post-decrement)
- --mat (pre-decrement)
  
Equality operators: (Checks only matrices values' sum)
- Equals (mat1 == mat2)
- Not equals (mat1 != mat2)
- Greater than (mat1 > mat2)
- Greater or equal (mat1 >= mat2)
- Less than (mat1 < mat2)
- Less or equal (mat1 <= mat2)

output operator(<< mat)
   
Additionaly to this operators I also implement rule of three that include:
1. Copy constructor
2. Assignment operator
3. Destructor

All the implementaion is in one file SquareMat.cpp and under namespace "Matrix".

Note that there are 2 kind of operators:
1. In class
2. Out class
   
I used Out class operators only where i have to, for example in the output operator and in the (scalar * matrix) operator
the first parameter is not of SquareMat object so i can't write it in class, because that "this" is always the first parametrs.
In other operators like (mat1 + mat2), (mat1 - mat2) etc, i prefer to use out class method, (even thow i could use in class)
Because that way i declare the first parameter as a copy object, and not pointer to the origin object,
and this way i ensure that i am not touching the original, but only use a copy
and that way i could change it in my function without change the original.

of course i put also the out class operator in the SquareMat.hpp file, 
for make them accessible for every one uses the class.
(The "friend" keyword was unnecessary because i didn't needed to access private members)

The project also contains a comprehensive test file of the class - SquareMatTest.cpp, a MAKE file with options to run from MAIN, from the tests, or to run valgrind.

The project has been tested by valgrind and have 0 memory leaks.

All 1732 lines of code in the project were written by me alone. During the implementation of the project, I did not resort to the help of AI at all, and I solved all the technical difficulties myself, in order to truly create an opportunity for myself to learn and solve challenges in the ultimate way.

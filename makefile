CXX=g++
CXXFLAGS=-std=c++2a -g -c

.PHONY: clean Main test valgrind build

Main: buildMain
	./main.out

test: buildTest
	./test.out

valgrind: buildMain buildTest
	valgrind --leak-check=yes ./main.out
	valgrind --leak-check=yes ./test.out

buildMain: main.o SquareMat.o
	$(CXX) $^ -o main.out

buildTest: SquareMatTest.o SquareMat.o
	$(CXX) $^ -o test.out

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

SquareMatTest.o: SquareMatTest.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

SquareMat.o: SquareMat.cpp SquareMat.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o *.out
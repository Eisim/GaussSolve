#include<iostream>
#include"Matrix.h"
#include"Vector.h"
#include"GaussSolve.h"
int main() {
	//size A:3 5   0 2 1 -1 1 1 1 3 -2 3 3 1 8 -4 0 3 1 2

	/*
	size A:5 5
9 7 8 8 8
8 8 8 8 8
5 5 5 5 5
1 1 9 1 2
9 8 4 7 8
1 9 2 -1 -1

*/

	int sizeA1, sizeA2;
	
	std::cout << "size A:";
	std::cin >> sizeA1 >> sizeA2;

	Matrix A(sizeA1, sizeA2);
	Vector b(sizeA1);
	std::cout << "enter elements:\n";
	//A.randomFill();
	//b.randomfill();
	//std::cout << A << b;
	std::cin >> A >> b;

	GaussSolve slv(A,b);

	test(A, b);

	std::cout <<"\n" << slv;

	return 0;
}
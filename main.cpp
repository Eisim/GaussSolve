#include<iostream>
#include"Matrix.h"
#include"Vector.h"
#include"GaussSolver.h"
int main() {

	//size A:3 5   0 2 1 -1 1 1 1 3 -2 3 3 1 8 -4 0 3 1 2


	int sizeA1, sizeA2;
	
	std::cout << "size A:";
	std::cin >> sizeA1 >> sizeA2;

	Matrix A(sizeA1, sizeA2);
	Vector b(sizeA1);
	std::cout << "enter elements:\n";
	A.randomFill();
	b.randomfill();
	std::cout << A << b;
	//std::cin >> A >> b;
 	GaussSolver slv;
	std::vector<Vector> solve = slv.solve(A, b);
	test(A, b);
	//std::cout << slv.getSolve()[0];
	std::cout <<"\n" << slv;

	return 0;
}
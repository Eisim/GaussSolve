#include<iostream>
#include"Matrix.h"
#include"Vector.h"
#include"GaussSolve.h"
int main() {
	//0 2 1 -1 1 1 1 3 -2 3 3 1 8 -4 0 3 1 2
	int sizeA1, sizeA2;
	std::cout << "size A:";
	std::cin >> sizeA1 >> sizeA2;
	
	Matrix A(sizeA1,sizeA2);
	Vector b(sizeA1);
	std::cin >> A >> b;

	GaussSolve slv;
	slv.solve(A, b);

	std::cout << slv;

	return 0;
}
#include<iostream>
#include"Matrix.h"
#include"Vector.h"
#include"GaussSolver.h"
int main() {

	//size A:3 5   0 2 1 -1 1 1 1 3 -2 3 3 1 8 -4 0 3 1 2
	
	/*size A : 7 5
	0 0 0 0 0
	0 1 0 -3 0
	0 0 -8 0 0
	0 0 0 0 0
	0 0 0 0 0
	0 0 0 0 5
	0 0 0 0 0

	0 4 -4 0 0 1 0
	
	size A:3 3

	-1 5 9
	3 -5 0
	2 0 9
	-1 2 1
	
	*/



	int sizeA1, sizeA2;
	
	std::cout << "size A:";
	std::cin >> sizeA1 >> sizeA2;

	Matrix A(sizeA1, sizeA2);
	Vector b(sizeA1);
	std::cout << "enter elements:\n";
	//A.randomFill();
	//b.randomfill();
	std::cout << A << b;
	std::cin >> A >> b;
 	GaussSolver slv;
	std::vector<Vector> solve = slv.solve(A, b);
	
	std::cout << "\n" << slv;

	//test(A, b);
	//std::cout << slv.getSolve()[0];
	

	return 0;
}
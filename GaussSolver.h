#pragma once
#include"Matrix.h"
#include<vector>
#include"Vector.h"

void test(Matrix& A, Vector& b);
std::vector<int> takeFreeElems(const std::vector<int> mainelems, int sizeA);
class GaussSolver {
private:

	int size;
	std::vector<Vector> vsolve;
	std::vector<int> mainelems;
	std::vector<int> freeelems;

	bool havesolve;

public:
	int getSize() { return size; }
	std::vector<Vector> solve(const Matrix& A, const Vector& b);
	bool checkSolvability() { return havesolve; }
	std::vector<int> getMainElems() { return mainelems; }
	std::vector<int> getFreeElems() { return freeelems; }
	std::vector<Vector> getSolve() { return vsolve; }
	double accuracy;
	GaussSolver() :havesolve(true),freeelems(0),size(0),vsolve(0),mainelems(0),accuracy(1e-10) {};
	GaussSolver(const Matrix& A, const Vector& b) :GaussSolver() { this->solve(A, b); size = A.size[1]; freeelems = takeFreeElems(mainelems, size);}

	
	friend std::ostream& operator<<(std::ostream& out, const GaussSolver& gs);

};
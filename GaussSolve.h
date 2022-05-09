#pragma once
#include"Matrix.h"
#include<vector>
#include"Vector.h"
class GaussSolve {
private:
	std::vector<Vector> vsolve;
	std::vector<int> mainelems;
public:
	GaussSolve() :vsolve(0),mainelems(0) {};

	std::vector<Vector> solve(const Matrix& A, const Vector& b);
	friend std::ostream& operator<<(std::ostream& out, const GaussSolve& gs);

};
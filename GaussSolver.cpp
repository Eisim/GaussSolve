#include"GaussSolver.h"
#include"Matrix.h"
#include<vector>
#include"Vector.h"
#include<cmath>

std::vector<int> takeFreeElems(const std::vector<int> mainelems, int sizeA) {
	bool isinmain;
	std::vector<int> a;
	for (int i = 0; i < sizeA; i++) {
		isinmain = false;
		for (int j = 0; j < mainelems.size(); j++) {
			if (i == mainelems[j]) isinmain = true;
		}
		if (!isinmain)a.push_back(i);
	}
	return a;
}

double myabs(double a) { return (a > 0) ? a : -a; }
int min(int a, int b) { return  (a <= b) ? a : b; }

bool comparisonWithConst(Matrix& m, const int num) {
	for (int i = 0; i < m.size[0]; i++)
		for (int j = 0; j < m.size[1]; j++)
			if (m[i][j] != num) return false;
	return true;
}
bool comparisonWithConst(Vector& v, const int num) {
	for (int i = 0; i < v.getSize(); i++)
			if (v[i] != num) return false;
	return true;
}

bool elemComporisonLess(Vector& v, double num) {
	for (int i = 0; i < v.getSize(); i++) {
		if (myabs(v[i]) >= num) return false;
	}
	return true;
}

std::vector<Vector> GaussSolver::solve(const Matrix&A,const Vector& b) {
	if (A.size[0] != b.getSize()) { havesolve = false; return this->vsolve; }
	
	Matrix copyA = A;
	Vector copyb = b;
	this->size = copyA.size[1];
	bool swaped;
	int minsize = min(A.size[0],A.size[1]);
	double mainelem;
	int MEindex[2];

	for (int i = 0; i < minsize; i++) {
		if (comparisonWithConst(copyA, 0) && comparisonWithConst(copyb, 0)) { havesolve = false; return this->vsolve; }
		bool TMP1 = elemComporisonLess(copyA[i], accuracy);
		bool TMP2 = elemComporisonLess(copyb, accuracy);
		if (TMP1 && !TMP2) {havesolve = false; return this->vsolve; }
		if (TMP1 && TMP2) continue;
		
		//swap to make the diagonal element main
		double max = A[i][i];
		int indexM = i;
		for (int j = i + 1; j < A.size[0]; j++) {
			if (A[j][i]>=accuracy && myabs(A[j][i]) > max) {
				max = myabs(A[j][i]);
				indexM = j;
			}
		}
		copyA.swap(i, indexM);
		copyb.swap(i, indexM);
		
		mainelem = copyA[i][i];
		MEindex[0] = i, MEindex[1] = i;
		if (myabs(mainelem) <= accuracy) {
			for (int j = 0; j < A.size[1]; j++)
				if (myabs(copyA[i][j]) > accuracy) {
					mainelem = copyA[i][j];
					MEindex[0]=i,MEindex[1]=j;
					break;
				}
		}
		
		mainelems.push_back(MEindex[1]);
		copyA[i]/= mainelem;
		copyb[i] /= mainelem;

		//change rows
		for (int j = 0; j < A.size[0]; j++) {
			if (j != MEindex[0]) {
				copyb[j] -= (copyb[MEindex[0]]*copyA[j][MEindex[1]]);
				copyA[j] -= (copyA[MEindex[0]] * copyA[j][MEindex[1]]);
				
			}
		}
		//check solvability
		for (int c = 0; c < A.size[0]; c++) {
			if (copyA[c]==0 && copyb[c]!=0){//(elemComporisonLess(copyA[c], accuracy) && myabs(copyb[c]) > accuracy) {
				havesolve = false;
				return this->vsolve;
			}
		}
	}

	std::vector<int>freeelems = takeFreeElems(mainelems, A.size[1]);

	//take result
	Vector solve(A.size[1]);
	for (int i = 0; i < mainelems.size(); i++) {
		solve[mainelems[i]] = copyb[i];
	}
	this->vsolve.push_back(solve);

	for (int j = 0; j < freeelems.size(); j++) {
		solve = A.size[1];
		for (int i = 0; i < mainelems.size(); i++) {
			solve[mainelems[i]] = -copyA[i][freeelems[j]];
			if(myabs(solve[mainelems[i]])<accuracy) solve[mainelems[i]]=0;
		}
		solve[freeelems[j]] = 1;
		vsolve.push_back(solve);
	}
	return this->vsolve;
	}

std::ostream& operator<<(std::ostream& out, const GaussSolver& gs) {
	if (gs.vsolve.size() == 0||!(gs.havesolve)) return out<<"No solution.";
	out << "(";
	for (int i = 0; i < gs.size; i++) {
		out << "x" << (i+1);
		if(i!=(gs.size-1)) out<<",";
	}
	out << ")=";

	for (int i = 0; i < gs.vsolve.size(); i++) {
		out << gs.vsolve[i];
		if (i != 0) out<<"t" << (i+1);
		if (i != (gs.vsolve.size() - 1)) out << "+";
	}
	out << "\n";

	return out;
}

double getNorm(const Matrix& m) {
	double norm = 0;
	double max = 0;
	for (int i = 0; i < m.size[0]; i++){
	for (int j = 0; j < m.size[1]; j++) 
			norm += myabs(m[i][j]);
		if (max < norm) max = norm;
		norm = 0;
	}
	return max;
}

void test( Matrix& A,Vector& b) {
	GaussSolver tmp(A,b);
	if (!tmp.checkSolvability()) { std::cout << "(TEST)No solution"; return ; }
	Matrix Mb(b.getSize(),1);
	for (int i = 0; i < b.getSize(); i++) Mb[i][0] = b[i];
	Matrix x(A.size[1],1);
	for (int i = 0; i < tmp.getMainElems().size(); i++) {
			x[tmp.getMainElems()[i]][0] = tmp.getSolve()[0][i];
	}
	Matrix Ax = A * x;
	
	double normAx = getNorm(Ax);
	double normb = getNorm(Mb);
	std::cout <<"norm Ax:" << normAx << "\nnorm b:" << normb << "\n";
	std::cout <<"norm difference:" << myabs(normAx - normb) << "\n";
	std::cout <<"test " << ((myabs(normAx - normb)<tmp.accuracy) ? "completed" : "failed");
}

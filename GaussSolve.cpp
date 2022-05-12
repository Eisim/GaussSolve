#include"GaussSolve.h"
#include"Matrix.h"
#include<vector>
#include"Vector.h"
#include<cmath>
#include<iomanip>
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

bool elemComporisonLess(Vector v,double num) {
	for (int i = 0; i < v.getSize(); i++) {
		if (v[i] >= num) return false;
	}
	return true;
}


std::vector<Vector> GaussSolve::solve(const Matrix&A,const Vector& b) {
	if (A.size[0] != b.getSize()) { havesolve = false; return this->vsolve; }
	
	Matrix copyA = A;
	Vector copyb = b;
	bool swaped;
	int minsize = min(A.size[0],A.size[1]);
	double mainelem;
	int MEindex[2];
	Vector solve(minsize);

	for (int i = 0; i < minsize; i++) {
		if (copyA[i]==0) continue;

		//swap to make the diagonal element main
		if (myabs(A[i][i]) <= accuracy)
		{
			for (int j = i + 1; j < A.size[0]; j++) {
				if (A[j][i] != 0) {
					copyA.swap(i, j);
					copyb.swap(i, j);
					break;
				}
			}
		}
		
		
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
	}

	

	//check solvability
	
	for (int c = 0; c < A.size[0]; c++) {
		if (elemComporisonLess(copyA[c],accuracy) && myabs(copyb[c]) > accuracy) {
			havesolve = false;
			return this->vsolve;
		}
	}
	



	this->vsolve.push_back(copyb);
	std::vector<int>freeelems = takeFreeElems(mainelems, A.size[1]);
	//for (int i = 0; i < mainelems.size(); i++) std::cout << "m:" << mainelems[i];
	//for (int i = 0; i < freeelems.size(); i++) std::cout <<"f:" << freeelems[i];
	

	//take result
	for (int j = 0; j < freeelems.size(); j++) {
		for (int i = 0; i < A.size[0]; i++) {
			solve[i] = -copyA[i][freeelems[j]];
		}
		vsolve.push_back(solve);
	}
	if (!havesolve) std::cout << "No solution." << std::endl;
	return this->vsolve;
	}

std::ostream& operator<<(std::ostream& out, const GaussSolve& gs) {
	if (gs.vsolve.size() == 0||!(gs.havesolve)) return out;
	out << "(";
	for (int i = 0; i < gs.mainelems.size(); i++) {
		out << "x" << gs.mainelems[i];
		if(i!=(gs.mainelems.size()-1)) out<<",";
	}
	out << ")=";

	for (int i = 0; i < gs.vsolve.size(); i++) {
		out << gs.vsolve[i];
		if (i != 0) out<<"t" << i;
		if (i != (gs.vsolve.size() - 1)) out << "+";
	}
	out << "\n";
	for (int i = 0; i < gs.freeelems.size(); i++) {
		out <<"\n" << "x" << gs.freeelems[i] << " = " << "t" << (i+1);
	}


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
	GaussSolve tmp(A,b);
	if (!tmp.checkSolvability()) { std::cout << "No solution"; return ; }
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

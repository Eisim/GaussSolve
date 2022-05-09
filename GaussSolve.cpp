#include"GaussSolve.h"
#include"Matrix.h"
#include<vector>
#include"Vector.h"

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


int min(int a, int b) { return  (a <= b) ? a : b; }


std::vector<Vector> GaussSolve::solve(const Matrix&A,const Vector& b) {
	if (A.size[0] != b.getSize()) return this->vsolve;
	
	Matrix copyA = A;
	Vector copyb = b;
	bool swaped;
	int minsize = min(A.size[0],A.size[1]);
	double mainelem;
	int MEindex[2];
	Vector solve(minsize);

	for (int i = 0; i < minsize; i++) {
		if (copyA[i] == 0) continue;

		//swap to make the diagonal element main
		if (A[i][i] == 0)
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
		if (mainelem == 0) {
			for (int j = 0; j < A.size[1]; j++)
				if (copyA[i][j] != 0) {
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
		if (copyA[c] == 0 && copyb[c] != 0) {
			std::cout << "No solution." << std::endl;
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
	return this->vsolve;
	}

std::ostream& operator<<(std::ostream& out, const GaussSolve& gs) {
	out << "(";
	for (int i = 0; i < gs.vsolve.size(); i++) {
		out << "x" << i;
		if(i!=(gs.vsolve.size()-1)) out<<",";
	}
	out << ")=";

	for (int i = 0; i < gs.vsolve.size(); i++) {
		out << gs.vsolve[i];
		if (i != 0) out<<"t" << i;
		if (i != (gs.vsolve.size() - 1)) out << "+";
	}
	out << "\n";
	return out;
}

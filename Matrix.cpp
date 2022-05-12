#include"Matrix.h"
#include"Vector.h"
#include<iostream>

Matrix::Matrix() {
	size[0] = 0;
	size[1] = 0;
	data = 0;
}

Matrix::Matrix(const int size1, const int size2) {
	this->size[0] = size1;
	this->size[1] = size2;
	data = new Vector[size[0]];
	for (int i = 0; i < size[0]; i++) {
		data[i].resize(size[1]);
		for (int j = 0; j < size[1]; j++)
			data[i][j] = 0;
	}
}
Matrix::Matrix(const Matrix& m) {
	size[0] = m.size[0];
	size[1] = m.size[1];
	data = new Vector[size[0]];
	for (int i = 0; i < size[0]; i++)
		data[i] = m.data[i];


}
Matrix::~Matrix() {
	delete[] data;
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (this == &m) { return *this; }
	size[0] = m.size[0]; size[1] = m.size[1];
	delete[] data;
	data = new Vector[size[0]];
	for (int i = 0; i < size[0]; i++)
		data[i] = m.data[i];

	return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (size[0] == m.size[0]) {
		for (int i = 0; i < size[0]; i++)
			data[i] += m.data[i];
	}
	else { std::cout << "ERROR +=\n"; return *this; }
	return *this;
}


Matrix& Matrix::operator-=(const Matrix& m) {
	if (size[0] == m.size[0]) {
		for (int i = 0; i < size[0]; i++)
			data[i] -= m.data[i];
	}
	else { std::cout << "ERROR -=\n"; return *this; }
	return *this;
}

Matrix& Matrix::operator*=(const int& num) {
		for (int i = 0; i < size[0]; i++)
			data[i] *=num;
	return *this;
}

Matrix Matrix::operator*(const int& num) const {
	Matrix result(size[0], size[1]);
	for (int i = 0; i < size[0]; i++) {
		result[i] = data[i] *num;
	}
	return result;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	if (size[1] != m.size[0]) return *this;
	Matrix result(size[0], m.size[1]);
	for (int i = 0; i < result.size[0]; i++) {
		for (int k = 0; k < size[1]; k++){
			for (int j = 0; j < result.size[1]; j++)
				result[i][j] += (data[i][k] * m[k][j]);
		}
	}
	*this = result;
	return *this;
}
Matrix Matrix :: operator*(const Matrix& m) const {
	if (size[1] != m.size[0]) return *this;
	Matrix result(size[0], m.size[1]);
	for (int i = 0; i < result.size[0]; i++) {
		for (int k = 0; k < size[1]; k++) {
			for (int j = 0; j < result.size[1]; j++)
				result[i][j] += (data[i][k] * m[k][j]);
		}
	}
	return result;

}
Matrix Matrix::operator+(const Matrix& m) const {
	if (m.size[0] != size[0] || m.size[1] != m.size[1]) {
		std::cout << "ERROR +" << std::endl;
		return *this;
	}
	Matrix result(m.size[0], m.size[1]);
	for (int i = 0; i < m.size[0]; i++) {
		result[i] = data[i] + m.data[i];
	}
	return result;
}
Matrix Matrix::operator-(const Matrix& m) const {
	if (m.size[0] != size[0] || m.size[1] != m.size[1]) {
		std::cout << "ERROR -" << std::endl;
		return *this;
	}
	Matrix result(m.size[0], m.size[1]);
	for (int i = 0; i < m.size[0]; i++) {
		result[i] = data[i] - m.data[i];
	}
	return result;
}

Matrix Matrix::operator-() const {
	Matrix result(size[0], size[1]);
	for (int i = 0; i < size[0]; i++) {
		result[i] = data[i] * (-1);
	}
	return result;
}


Vector& Matrix::operator[](int i) {
	return this->data[i];
}
Vector Matrix::operator[](int i) const {
	return this->data[i];
}

void Matrix::randomFill() {
	for (int i = 0; i < size[0]; i++)
		data[i].randomfill();

}


std::ostream& operator<<(std::ostream& out, const Matrix& m) {
	out << "[\n";
	for (int i = 0; i < m.size[0]; i++)
		out << m.data[i]<<"\n";
	out << "]";
	out <<"\n";
	return out;
}
void Matrix::swap(int i, int j) {
	Vector tmp=data[i];
	data[i] = data[j];
	data[j] = tmp;
}

std::istream& operator>>(std::istream& in, Matrix& m) {
	for (int i = 0; i < m.size[0]; i++) {
		for (int j = 0; j < m.size[1]; j++) {
			std::cin >> m[i][j];
		}
	}
	return in;
}
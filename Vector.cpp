#include"Vector.h"
#include<iostream>


Vector::Vector() : n(0), data(0) {

}

Vector::Vector(int n) {
	this->n = n;
	this->data = new double[n];
	for (int i = 0; i < n; i++)
		data[i] = 0.;
}

Vector::Vector(const Vector& v) {
	this->n = v.n;
	this->resize(v.n);
	for (int i = 0; i < n; i++)
		this->data[i] = v[i];

}


Vector::~Vector() {
	delete[] data;

}



Vector& Vector::operator+=(const Vector& v) {
	if (this->n != v.n) {
		std::cout << "ERROR in operator+=" << std::endl;
		return *this;
	}
	for (int i = 0; i < n; i++)
		this->data[i] += v.data[i];
	return *this;

}
Vector& Vector::operator-=(const Vector& v) {
	if (this->n != v.n) {
		std::cout << "ERROR in operator-=" << std::endl;
		return *this;
	}
	for (int i = 0; i < n; i++)
		this->data[i] -= v.data[i];
	return *this;

}
Vector& Vector::operator*=(double c) {
	for (int i = 0; i < n; i++)
		this->data[i] *= c;
	return *this;

}
Vector& Vector::operator/=(double c) {
	for (int i = 0; i < n; i++)
		this->data[i] /= c;
	return *this;

}

void Vector::resize(int newSize) {
	if (newSize >= 0) {
	delete[] data;
		this->data = new double[newSize];
		this->n = newSize;
		for (int i = 0; i < n; i++)
			data[i] = 0;
	}
}


double& Vector::operator[](int i) {
	if (i >= n || i < 0) {
		std::cout << "ERROR IN operator[]1\n";
		return this->data[0];
	}
	return this->data[i];
}
double Vector::operator[](int i) const {
	if (i >= n || i < 0) {
		std::cout << "ERROR IN operator[]2\n";
		return this->data[0];
	}
	return this->data[i];
}

Vector& Vector::operator=(const Vector& v) {
	if (this != &v) {
		if (v.n != this->n)
			this->resize(v.n);
		for (int i = 0; i < v.n; i++)
			this->data[i] = v.data[i];
	}
	return *this;
}


Vector Vector::operator+(const Vector& v) const {
	if (v.n != n) {
		std::cout << "ERROR in operator+" << std::endl;
		return *this;
	}
	Vector res(v.n);
	for (int i = 0; i < v.n; i++) {
		res[i] = this->data[i] + v.data[i];
	}
	return res;
}

Vector Vector::operator-(const Vector& v) const {
	if (v.n != n) {
		std::cout << "ERROR in operator+" << std::endl;
		return *this;
	}
	Vector res(v.n);

	for (int i = 0; i < v.n; i++)
		res.data[i] = this->data[i] - v.data[i];
	return res;
}

Vector Vector::operator*(double c) const {
	Vector res(n);

	for (int i = 0; i < n; i++)
		res.data[i] = this->data[i] * c;
	return res;
}
Vector Vector::operator/(double c) const {
	Vector res(n);

	for (int i = 0; i < n; i++)
		res.data[i] = this->data[i] / c;
	return res;
}

double Vector::getNorm() const {
	return std::sqrt(this->dot(*this));
}

double Vector::dot(const Vector& v) const {
	double res = 0;

	for (int i = 0; i < n; i++)
		res += this->data[i] * v[i];
	return res;
}


int Vector::getSize() const {
	return this->n;
}

void Vector::randomfill() {
	
	for (int i = 0; i < this->n; i++)
		this->data[i] = rand() % 100;

}

void Vector::print() const {
	std::cout << "(";
	for (int i = 0; i < this->n; i++) {
		std::cout << this->data[i];
		if ((i + 1) != this->n)
			std::cout << ",";
	}
	std::cout << ")";
	std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Vector& v) {
	out << "(";
	for (int i = 0; i < v.n; i++) {
		out << v.data[i];
		if ((i + 1) != v.n)
			out << ",";
	}
	out << ")";
	return out;
}

std::istream& operator>>(std::istream& in, Vector& v) {
	for (int i = 0; i < v.getSize(); i++) {
			std::cin >> v[i];
		
	}
	return in;
}

void Vector::swap(int i, int j) {
	if (i == j) return;
	double tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}

Vector operator*(double c, Vector& v) {

	return v * c;
}
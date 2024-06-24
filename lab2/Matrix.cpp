#include "Matrix.h"
#include "Vector.h"
#include <math.h>
#include <iostream>
#include "IncompatibleDimException.h"

CSRMatrix::CSRMatrix() :
	m_MatrDim(0.),
	m_aelem_size(0.),
	m_aelem(nullptr),
	m_jptr(nullptr),
	m_iptr(nullptr)
{}

CSRMatrix::CSRMatrix(const double* p_aelems, const int* p_jptrs, const int* p_iptrs, int p_matr_dim, int p_AelemSize) {
	m_MatrDim = p_matr_dim;
	m_aelem_size = p_AelemSize;
	m_aelem = new double[m_aelem_size];
	for (int i = 0; i < m_aelem_size; i++) 
		m_aelem[i] = p_aelems[i];
	m_jptr = new int[m_aelem_size];
	for (int i = 0; i < m_aelem_size; i++) 
		m_jptr[i] = p_jptrs[i];
	m_iptr = new int[m_MatrDim + 1];
	for (int i = 0; i <= m_MatrDim; i++) 
		m_iptr[i] = p_iptrs[i];
}

CSRMatrix::CSRMatrix(const CSRMatrix& p_matr):
	m_MatrDim(p_matr.m_MatrDim),	
	m_aelem_size(p_matr.m_aelem_size)
{
	m_aelem = new double[m_aelem_size];
	for (int i = 0; i < m_aelem_size; i++)
		m_aelem[i] = p_matr.m_aelem[i];
	m_jptr = new int[m_aelem_size];
	for (int i = 0; i < m_aelem_size; i++)
		m_jptr[i] = p_matr.m_jptr[i];
	m_iptr = new int[m_MatrDim + 1];
	for (int i = 0; i <= m_MatrDim; i++)
		m_iptr[i] = p_matr.m_iptr[i];
}

CSRMatrix& CSRMatrix:: operator=(const CSRMatrix& p_matr) {
	if (this == &p_matr)
		return *this;

	if (m_aelem_size != p_matr.m_aelem_size) {
		delete[] m_aelem;
		delete[] m_jptr;
		m_aelem_size = p_matr.m_aelem_size;
		m_aelem = new double[m_aelem_size];
		m_jptr = new int[m_aelem_size];
	}
	if (m_MatrDim != p_matr.m_MatrDim) {
		delete[] m_iptr;
		m_MatrDim = p_matr.m_MatrDim;
		m_iptr = new int[m_MatrDim + 1];
	}
	for (int i = 0; i < m_aelem_size; i++)
		m_aelem[i] = p_matr.m_aelem[i];
	for (int i = 0; i < m_aelem_size; i++)
		m_jptr[i] = p_matr.m_jptr[i];
	for (int i = 0; i <= m_MatrDim; i++)
		m_iptr[i] = p_matr.m_iptr[i];
	return *this;
}

std::istream& operator >> (std::istream& p_in, CSRMatrix& p_matr) {
	std::cout << "введите размер aelem: ";
	p_in >> p_matr.m_aelem_size;
	if(p_matr.m_aelem != nullptr)
		delete[] p_matr.m_aelem;
	if (p_matr.m_jptr != nullptr)
		delete[] p_matr.m_jptr;
	p_matr.m_aelem = new double[p_matr.m_aelem_size];
	p_matr.m_jptr = new int[p_matr.m_aelem_size];
	std::cout << "введите aelem: " << std::endl;;
	for (int i = 0; i < p_matr.m_aelem_size; i++) 
		p_in >> p_matr.m_aelem[i];
	std::cout << "введите jptr" << std::endl;
	for (int i = 0; i < p_matr.m_aelem_size; i++) 
		p_in >> p_matr.m_jptr[i];
	std::cout << "введите размерность матрицы: ";
	p_in >> p_matr.m_MatrDim;
	if (p_matr.m_iptr != nullptr)
		delete[] p_matr.m_iptr;
	p_matr.m_iptr = new int[p_matr.m_MatrDim + 1];
	std::cout << "введите iptr: " << std::endl;
	for (int i = 0; i <= p_matr.m_MatrDim; i++) 
		p_in >> p_matr.m_iptr[i];
	return p_in;
}

std::ostream& operator << (std::ostream& p_out, const CSRMatrix& p_matr) {
	p_out << "aelem: [ ";
	for (int i = 0; i < p_matr.m_aelem_size; i++) 
		p_out << p_matr.m_aelem[i] << ' ';
	p_out << "]" << std::endl;
	p_out << "jptr: [ ";
	for (int i = 0; i < p_matr.m_aelem_size; i++) 
		p_out << p_matr.m_jptr[i] << ' ';
	p_out << "]" << std::endl;
	p_out << "iptr: [ ";
	for (int i = 0; i <= p_matr.m_MatrDim; i++) 
		p_out << p_matr.m_iptr[i] << ' ';
	p_out << "]" << std::endl;
	return p_out;
}

int CSRMatrix::MatrDimen() const{
	return m_MatrDim;
}

int CSRMatrix::NonNul() const{
	return m_aelem_size;
}

CSRMatrix operator*(double a, const CSRMatrix& p_matr) {
	CSRMatrix result(p_matr.m_aelem, p_matr.m_jptr, p_matr.m_iptr, p_matr.m_MatrDim, p_matr.m_aelem_size);
	for (int i = 0; i < result.m_aelem_size; i++) {
		result.m_aelem[i] *= a;
	}
	return result;
}

CSRMatrix CSRMatrix::operator*(double p_a) {
	return p_a * (*this);
}

Vector CSRMatrix::operator*(const Vector& p_vec) {
	if (m_MatrDim != p_vec.m_dimension)
		throw IncompatibleDimException("Ошибка размерности вектора и матрицы!");
	Vector result(m_MatrDim);
	for (int i = 0; i < m_MatrDim; i++) {
		for (int j = m_iptr[i] - 1; j < m_iptr[i + 1] - 1; j++) {
			result[i] += p_vec[m_jptr[j]-1] * m_aelem[j];
		}
	}
	return result;
}

CSRMatrix::~CSRMatrix() {
	delete[] m_aelem; 
	delete[] m_jptr;
	delete[] m_iptr;
}

//данные для быстрого ввода теста:
//введите размер aelem : 25
//введите aelem :
//9 3 1 1 11 2 1 2 1 10 2 2 1 2 9 1 1 1 12 1 8 2 2 3 8
//введите jptr
//1 4 5 7 2 3 4 7 2 3 4 1 2 3 4 5 1 4 5 7 6 1 2 5 7
//введите размерность матрицы : 7
//введите iptr :
//1 5 9 12 17 21 22 26
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Vector;


class CSRMatrix {
private:
	int m_MatrDim;
	int m_aelem_size;
	double* m_aelem;
	int* m_jptr;
	int* m_iptr;
	friend class Vector;
public:
	CSRMatrix();//конструктор
	explicit CSRMatrix(const double* p_aelems, const int* p_jptrs, const int* p_iptrs, int p_matr_dim, int p_AelemSize); //конструктор с параметрами
	CSRMatrix(const CSRMatrix& p_matr);
	int MatrDimen() const;
	int NonNul() const;

	CSRMatrix& operator=(const CSRMatrix& p_matr); //присваивание
	CSRMatrix operator*(double p_a);
	Vector operator*(const Vector& p_vec);
	friend CSRMatrix operator*(double p_a, const CSRMatrix& p_matr);
	friend std::istream& operator >> (std::istream& p_in, CSRMatrix &p_matr);
	friend std::ostream& operator << (std::ostream& p_out, const CSRMatrix &p_matr);
	~CSRMatrix();
};
#endif
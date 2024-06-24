#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class CSRMatrix;

class Vector {
private:
	double* m_vector;
	int m_dimension; //�����������
	friend class CSRMatrix;
public:
	Vector();//�����������
	explicit Vector(int p_n); //����������� � �����������
	Vector(const Vector& p_vec);//����������� �����������
	Vector(const std::initializer_list<double> p_c);
	void SetDimension(int p_n); //����������� ����������� �������
	double Length() const;//����������� ����� �������
	int GetDimension() const;

	//��������� ��������
	
	Vector& operator=(const Vector& p_vec); //������������

	bool operator!=(const Vector& p_vec) const;
	bool operator==(const Vector& p_vec) const;
	Vector& operator+=(double p_a);
	Vector& operator-=(double p_a);
	Vector& operator+=(const Vector& p_vec);
	Vector& operator-=(const Vector& p_vec);

	Vector& operator+();
	Vector operator-();
	Vector operator+(double p_a);
	Vector operator-(double p_a);
	Vector operator+(const Vector& p_vec);
	Vector operator-(const Vector& p_vec);

	double operator*(const Vector& p_vec) const; //��������� ������������ ��������
	Vector operator*(double p_a) const;//������������ ������� �� �����

	const double& operator[](int p_index) const;	//���������� ��������� �������������� ��� ������
	double& operator[](int p_index); //��� ������

	explicit operator double* () const;//�������� ���������� ����

	//���������� �������� �����/������ � �����
	friend std::ostream& operator << (std::ostream& p_out, const Vector& p_vec);
	friend std::istream& operator >> (std::istream& p_in, const Vector& p_vec);
	
	friend Vector operator*(double p_a, const Vector& p_vec);
	Vector operator*(const CSRMatrix& p_matr);
	~Vector();//����������
};
#endif
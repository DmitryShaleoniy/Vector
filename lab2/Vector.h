#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class CSRMatrix;

class Vector {
private:
	double* m_vector;
	int m_dimension; //размерность
	friend class CSRMatrix;
public:
	Vector();//конструктор
	explicit Vector(int p_n); //конструктор с параметрами
	Vector(const Vector& p_vec);//конструктор копирования
	Vector(const std::initializer_list<double> p_c);
	void SetDimension(int p_n); //определение размерности вектора
	double Length() const;//определение длины вектора
	int GetDimension() const;

	//пергрузка операций
	
	Vector& operator=(const Vector& p_vec); //присваивание

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

	double operator*(const Vector& p_vec) const; //скалярное произведение векторов
	Vector operator*(double p_a) const;//произведение вектора на число

	const double& operator[](int p_index) const;	//перегрузка оператора индексирования для чтения
	double& operator[](int p_index); //для записи

	explicit operator double* () const;//оператор приведения типа

	//перегрузка операции ввода/вывода в поток
	friend std::ostream& operator << (std::ostream& p_out, const Vector& p_vec);
	friend std::istream& operator >> (std::istream& p_in, const Vector& p_vec);
	
	friend Vector operator*(double p_a, const Vector& p_vec);
	Vector operator*(const CSRMatrix& p_matr);
	~Vector();//деструктор
};
#endif
#include "Vector.h"
#include "Matrix.h"
#include <math.h>
#include <iostream>
#include "IncompatibleDimException.h"
#include "OutOfRangeException.h"
#include <cmath>
#include <limits>

bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

Vector::Vector(): 
    m_dimension(0.),
    m_vector(nullptr)
{}

Vector::Vector(int p_n) :
    m_dimension(p_n)
{
    m_vector = new double[p_n];
    for (int i = 0; i < p_n; i++) {
        m_vector[i] = 0;
    }
}

Vector::Vector(const std::initializer_list<double> p_c) :
    m_dimension(p_c.size())
{
    m_vector = new double[m_dimension];
    for (int i = 0; i < m_dimension; i++)
        m_vector[i] = *(p_c.begin()+i);
}

Vector::Vector(const Vector& p_vec): //конструктор копировани€
    m_dimension(p_vec.m_dimension)
{ 
    m_vector = new double[m_dimension];
    for (int i = 0; i < m_dimension; i++)
        m_vector[i] = p_vec.m_vector[i];
}

double Vector::Length() const{
    double sum = 0;
    for (int i = 0; i < m_dimension; i++) {
        sum += m_vector[i] * m_vector[i];
    }
    return (double)sqrt(sum);
}

int Vector::GetDimension() const{
    return m_dimension;
}

void Vector::SetDimension(int p_n) { //сеттер
    m_dimension = p_n;
}
//операции
Vector& Vector::operator=(const Vector& p_vec) {
    if (this == &p_vec)
        return *this;
    if (m_dimension != p_vec.m_dimension) {
        delete[] m_vector;
        m_dimension = p_vec.m_dimension;
        m_vector = new double[m_dimension];
    }
    for (int i = 0; i < m_dimension; i++) {
        m_vector[i] = p_vec.m_vector[i];
    }
    return *this;
}

bool Vector::operator==(const Vector& p_vec) const{
    if (m_dimension != p_vec.m_dimension)
        return false;
    for (int i = 0; i < m_dimension; i++) {
        if (!(is_equal(m_vector[i], p_vec.m_vector[i])))
            return false;
    }
    return true;
}

bool Vector::operator!=(const Vector& p_vec) const{
    return !(*this == p_vec);
}

Vector& Vector::operator+=(double p_a) {
    for (int i = 0; i < m_dimension; i++)
        m_vector[i] += p_a;
    return *this;
}

Vector& Vector::operator-=(double p_a) {
    for (int i = 0; i < m_dimension; i++)
        m_vector[i] -= p_a;
    return *this;
}

Vector& Vector::operator+=(const Vector& p_vec) {
    if (m_dimension != p_vec.m_dimension)
        throw IncompatibleDimException("ќшибка размерностей векторов!");
    for (int i = 0; i < m_dimension; i++)
        m_vector[i] += p_vec.m_vector[i];
    return *this;
}

Vector& Vector::operator-=(const Vector& p_vec) {
    if (m_dimension != p_vec.m_dimension)
        throw IncompatibleDimException("ќшибка размерностей векторов!");
    for (int i = 0; i < m_dimension; i++)
        m_vector[i] -= p_vec.m_vector[i];
    return *this;
}

Vector &Vector::operator+() {
    return *this;
}

Vector Vector::operator-() {
    Vector result(*this);
    for (int i = 0; i < m_dimension; i++)
        result[i] *= -1;
    return result;
}

Vector Vector::operator+(double p_a) {
    Vector result(*this);
    for (int i = 0; i < m_dimension; i++)
        result.m_vector[i] += p_a;
    return result;
}

Vector Vector::operator-(double p_a) {
    Vector result(*this);
    for (int i = 0; i < m_dimension; i++)
        result.m_vector[i] -= p_a;
    return result;
}

Vector Vector::operator+(const Vector& p_vec) {
    if (m_dimension != p_vec.m_dimension)
        throw IncompatibleDimException("ќшибка размерностей векторов!");
    Vector result(*this);
    for (int i = 0; i < m_dimension; i++) 
        result.m_vector[i] += p_vec.m_vector[i];
    return result;
}

Vector Vector::operator-(const Vector& p_vec) {
    if (m_dimension != p_vec.m_dimension)
        throw IncompatibleDimException("ќшибка размерностей векторов!");
    Vector result(*this);
    for (int i = 0; i < m_dimension; i++)
        result.m_vector[i] -= p_vec.m_vector[i];
    return result;
}

double Vector:: operator*(const Vector& p_vec) const{ //скал€рное произведение векторов
    if (m_dimension != p_vec.m_dimension)
        throw IncompatibleDimException("ќшибка размерностей векторов!");
    double result = 0;
    for (int i = 0; i < m_dimension; i++)
        result += m_vector[i] * p_vec.m_vector[i];
    return result;
}

Vector operator*(double p_a, const Vector& p_vec) { //умножение числа на вектор
    Vector result(p_vec);
    for (int i = 0; i < p_vec.m_dimension; i++)
        result.m_vector[i] *= p_a;
    return result;
}

Vector Vector:: operator*(double p_a) const {
    return p_a * (*this);
}

Vector Vector::operator*(const CSRMatrix& p_matr) {
    if (m_dimension != p_matr.m_MatrDim)
        throw IncompatibleDimException("ќшибка размерности вектора и матрицы!");
    Vector result(p_matr.m_MatrDim);
    for (int i = 0; i < p_matr.m_MatrDim; i++) {
        result[i] = 0;
        int vec_ind = 0;
        int iptr_ind = 0;
        for (int j = 0; j < p_matr.m_aelem_size; j++) {
            if (p_matr.m_jptr[j] - 1 == i)
                result[i] += m_vector[iptr_ind] * p_matr.m_aelem[j];
            if (p_matr.m_iptr[iptr_ind + 1] - p_matr.m_iptr[0] == j + 1)
                iptr_ind++;
        }
    }
    return result;
}

const double& Vector:: operator[](int p_index) const { //оператор индексировани€[]
    if (p_index >= m_dimension)
        throw OutOfRangeException("»спользование необъ€вленной пам€ти");
    return m_vector[p_index];
}

double& Vector:: operator[](int p_index) {
    if (p_index >= m_dimension)
        throw OutOfRangeException("»спользование необъ€вленной пам€ти");
    return m_vector[p_index];
}

Vector::operator double*() const{ //оператор приведени€ типа
    return m_vector;
}

//перегрузка операции ввода/вывода в поток
std::ostream& operator << (std::ostream& p_out, const Vector& p_vec) {
    p_out << "[ ";
    for (int i = 0; i < p_vec.m_dimension; i++)
        p_out << p_vec.m_vector[i] << " ";
    p_out << "]";
    return p_out;
}

std::istream& operator >> (std::istream& p_in, const Vector& p_vec) {
    for (int i = 0; i < p_vec.m_dimension; i++)
        p_in >> p_vec.m_vector[i];
    return p_in;
}

Vector::~Vector() { //деструктор
    delete[] m_vector;
}
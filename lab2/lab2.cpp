#include <iostream>
#include "Vector.h"
#include "IncompatibleDimException.h"
#include "OutOfRangeException.h"

using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	int dim1, dim2;
	cout << "введите размерность для vector1: ";
	cin >> dim1;
	Vector vector1(dim1);
	cout << "vector 1: " << vector1 << " Length: " << vector1.Length() << endl;
	cout << "введите содержимое vector1:"<<endl;
	cin >> vector1;
	cout << "vector 1: " << vector1 << " Length: " << vector1.Length() << " //вывод вектора на экран и определение его длины" << endl;
	cout << "введите размерность для vector2: ";
	cin >> dim2;
	Vector vector2(dim2);
	cout << "vector 1: " << vector2 << " Length: " << vector2.Length() << endl;
	cout << "введите содержимое vector2:" << endl;
	cin >> vector2;
	cout << "vector 2: " << vector2 << " Length: " << vector2.Length() << endl;
	cout << "vector 1 + vector 2 = ";
	try { cout << vector1 + vector2 << " //оператор сложения векторов" << endl;}
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector 1 - vector 2 = ";
	try { cout << vector1 - vector2 << " //оператор вычетания векторов" << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector1 * vector2 = ";
	try { cout << (vector1 * vector2) << " //скалярное произвеление векторов" << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector1 += vector2 ";
	try { cout << (vector1 += vector2) << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector1 -= vector2 ";
	try { cout << (vector1 -= vector2) << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	vector2 = vector1;
	cout << "vector 2 = vector 1. vector 2: " << vector2 << " //оператор присваивания" << endl;
	cout << "vector 1 + vector 2 = ";
	try { cout << vector1 + vector2 << " //оператор сложения векторов" << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector 1 - vector 2 = ";
	try { cout << vector1 - vector2 << " //оператор вычетания векторов" << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector1 * vector2 = ";
	try { cout << (vector1 * vector2) << " //скалярное произвеление векторов" << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector1 += vector2 ";
	try { cout << (vector1 += vector2) << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector1 -= vector2 ";
	try { cout << (vector1 -= vector2) << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector 2 == vector 1: " << (vector2 == vector1) << " //проверка на равенство" << endl;
	cout << "vector 2 != vector 1: " << (vector2 != vector1) << " //проверка на неравенство" << endl;
	cout << "vector2[0] = ";
	
	try { cout << vector2[0] << " //оператор индексирования для чтения" << endl; }
	catch (OutOfRangeException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	
	cout << "vector2[vector2.GetDimension()] = 0. ";
	try {
		vector2[vector2.GetDimension()] = 0;
		cout << "vector 2: " << vector2 << " //оператор индексирования для записи" << endl;
	}
	catch (OutOfRangeException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector2[0] = 0 ";
	try {
		vector2[0] = 0;
		cout << "vector 2: " << vector2 << " //оператор индексирования для записи" << endl;
	}
	catch (OutOfRangeException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "vector 2 == vector 1: " << (vector2 == vector1) << " //проверка на равенство" << endl;
	cout << "vector 2 != vector 1: " << (vector2 != vector1) << " //проверка на неравенство" << endl;
	cout << "+vector1: " << vector1 << " //оператор +" << endl; 
	cout << "-vector1" << (-vector1) << " //оператор -" << endl;
	cout << "vector1 += 1" << (vector1 += 1) << endl;
	cout << "vector1 -= 1" << (vector1 -= 1) << endl;
	cout << "vector1 + 1" << (vector1 + 1) << " //оператор сложения вектора и  числа" << endl;
	cout << "vector1 - 1" << (vector1 - 1) << " //оператор вычетания вектора и  числа" << endl;
	cout << "vector1 * 2: " << (vector1 * 2) << " //умножение вектора на число" << endl;
	cout << "2 * vector1" << (2 * vector1) << endl;

	initializer_list<double> c{ 12, 17, 3, 7, 8.22 };
	Vector InitializerVector(c);
	Vector z{ 1,2,3,4, };
	cout << "\nсодержимое вектора z: " << z << endl;
	cout << "\nсодержимое вектора InitializerVector: " << InitializerVector << endl;
	cout << "InitializerVector + 2" << (InitializerVector + 2) << endl;
	cout << "длина вектора InitializerVector: " << InitializerVector.Length() << endl;
	cout << "InitializerVector * 3" << (InitializerVector * 3) << endl;

	CSRMatrix matr;
	CSRMatrix matr2;
	cout << "ввод matr: " << endl;
	cin >> matr;
	cout << matr;
	cout << "количество ненулевых элементов: " << matr.NonNul() << endl;
	cout << "размероность матрицы: " << matr.MatrDimen() << endl;
	cout << "matr * 2 = " <<endl << (matr * 2) << endl;
	cout << "2 * matr = "<< endl << (2 * matr) << endl;
	cout << "vector1 * matr = ";
	try { cout << (vector1* matr) << endl; }
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "matr * vector1 = " ;
	try {
		cout << (matr * vector1) << endl;
	}
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	cout << "ввод matr2:" << endl;
	cin >> matr2;
	matr2 = matr;
	cout << "matr2 = matr; matr: " << matr2 << endl;

	cout << vector1 << " vector1" << endl;
	cout << vector2 << " vector2" << endl;
	cout << "((matr * vector1)*(vector2 + vector1))*2 = ";
	try {
		cout << ((matr * vector1) * (vector2 + vector1)) * 2 << endl;
	}
	catch (IncompatibleDimException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
	catch (OutOfRangeException& ex) {
		cout << ex.what() << ex.GetErr() << endl;
	}
}
#include <iostream>
#include <exception>
#include "Vector.h"
#include "Matrix.h"
#include "OutOfRangeException.h"

OutOfRangeException::OutOfRangeException(const std::string& p_msg): 
	m_err(p_msg)
{}

const std::string OutOfRangeException::GetErr() const {
	return m_err;
}

const char* OutOfRangeException::what() const {
	return "Ошибка диапозона: ";
}
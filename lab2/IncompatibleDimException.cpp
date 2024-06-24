#include <iostream>
#include <exception>
#include "Vector.h"
#include "Matrix.h"
#include "IncompatibleDimException.h"

IncompatibleDimException::IncompatibleDimException(const std::string& p_msg) :
	m_err(p_msg)
{}

const std::string IncompatibleDimException :: GetErr() const{
	return m_err;
}

const char* IncompatibleDimException::what() const{
	return "Ошибка размерностей: ";
}
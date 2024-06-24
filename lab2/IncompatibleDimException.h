#ifndef INCOMPATIBLEDIMEXCEPTION_H
#define INCOMPATIBLEDIMEXCEPTION_H

#include <iostream>
#include <exception>
#include "Vector.h"
#include "Matrix.h"

class IncompatibleDimException :public std::exception {
public:
	IncompatibleDimException(const std::string& p_msg);
	virtual const char* what() const override;
	const std::string GetErr() const;
private:
	std::string m_err;
};

#endif
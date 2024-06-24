#ifndef OUTOFRANGEEXCEPTION_H
#define OUTOFRANGEEXCEPTION_H

#include <iostream>
#include <exception>
#include "Vector.h"
#include "Matrix.h"
#include <string>

class  OutOfRangeException :public std::exception {
public:
	OutOfRangeException(const std::string& p_msg);
	virtual const char* what() const override;
	const std::string GetErr() const;
private:
	std::string m_err;
};
#endif
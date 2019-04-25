#pragma once
#include "Header.h"

class MatrixException : public exception
{
public:
	const char * what() const throw()
	{
		return "Matrix size is too big.\n";
	}
};

class AnimalException : public exception
{
public:
	const char * what() const throw()
	{
		return "Too many animals for this matrix size.\n";
	}
};
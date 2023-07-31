#pragma once
#include <vector>
#include <iostream>
#include <string.h>

class Matrix4
{
	private:
		float _m[16];
	public:
		Matrix4();
		~Matrix4();
		float	&operator[](size_t index);
		float	operator[](size_t index);
};

std::ostream	&operator<<(std::ostream &os, const Matrix4 &matrix);
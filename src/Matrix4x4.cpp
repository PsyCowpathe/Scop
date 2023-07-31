#include "../headers/Matrix4x4.hpp"

Matrix4::Matrix4()
{
	// Note: this should be faster than anything else
	// but I don't know how it behaves with static arrays
	memset(_m, 0, 16 * sizeof(float));
	_m[0] = 1.0f;
	_m[5] = 1.0f;
	_m[10] = 1.0f;
	_m[15] = 1.0f;
}

Matrix4::~Matrix4()
{

}

float	&Matrix4::operator[](size_t index)
{
	if (index < 0 || index > 15)
	{
		std::cout << "Index out of array for Matrix4" << std::endl;
		exit(-1);
	}
	return(_m[index]);
}

float	Matrix4::operator[](size_t index)
{
	if (index < 0 || index > 15)
	{
		std::cout << "Index out of array for Matrix4" << std::endl;
		exit(-1);
	}
	return(_m[index]);
}


std::ostream	&operator<<(std::ostream &os, const Matrix4 &matrix)
{
	os << "| " << matrix[0];
}

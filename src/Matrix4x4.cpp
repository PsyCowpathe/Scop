#include "../headers/Matrix4x4.hpp"

/*	MATRIX
//	Constuctors and destructors
*/

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

/*	MATRIX
//	Utils
*/

void	Matrix4::print()
{
	std::cout << "| " << _m[0] << ", " << _m[1] << ", " << _m[2] << ", " << _m[3] << " |\n"
	<< "| " << _m[4] << ", " << _m[5] << ", " << _m[6] << ", " << _m[7] << " |\n"
	<< "| " << _m[8] << ", " << _m[9] << ", " << _m[10] << ", " << _m[11] << " |\n"
	<< "| " << _m[12] << ", " << _m[13] << ", " << _m[14] << ", " << _m[15] << " |" << std::endl;
}

/*	MATRIX
//	Operator overloading
*/

float	&Matrix4::operator[](size_t index)
{
	if (index < 0 || index > 15)
	{
		std::cout << "Index out of array for Matrix4" << std::endl;
		exit(-1);
	}
	return(_m[index]);
}

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

Matrix4::Matrix4(float list[16])
{
	memcpy(_m, list, 16 * sizeof(float));
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

Vec4	Matrix4::operator*(const Vec4 &other)
{
	float	x = other.getX();
	float	y = other.getY();
	float	z = other.getZ();
	float	w = other.getW();

	// TODO: check for perf impact
	Vec4	res(
		(_m[0] * x + _m[1] * y + _m[2] * z + _m[3] * w),
		(_m[4] * x + _m[5] * y + _m[6] * z + _m[7] * w),
		(_m[8] * x + _m[9] * y + _m[10] * z + _m[11] * w),
		(_m[12] * x + _m[13] * y + _m[14] * z + _m[15] * w)
	);
	return (res);
}

Matrix4	Matrix4::operator*(const Matrix4 &other)
{
	Matrix4	res;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			for (int k = 0; k < 4; k++)
			{
				res[row * 4 + col] += (_m[row * 4 + k] * other._m[k * 4 + col]);
				std::cout << "m: " << _m[row * 4 + k] << "other: " << other._m[k * 4 + col] << std::endl;
				std::cout << "calc: " << _m[row * 4 + k] * other._m[k * 4 + col] << std::endl;
				std::cout << "res: " << res[row * 4 + col] << std::endl;
			}
			exit(0);
		}
	}
	return (res);
}
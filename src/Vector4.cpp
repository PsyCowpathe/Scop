#include "../headers/Vector4.hpp"

Vec4::Vec4(float x, float y, float z, float w)
{
	_v[0] = x;
	_v[1] = y;
	_v[2] = z;
	_v[3] = w;
}

Vec4::~Vec4()
{

}

void	Vec4::print()
{
	std::cout << "<" << _v[0] << ", " << _v[1] << ", " << _v[2] << ", " << _v[3] << ">" << std::endl;
}
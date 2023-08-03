#include "../headers/Vector4.hpp"


/*	VEC4
//	constructors/destructors
*/
Vec4::Vec4()
{
	_v[0] = 0;
	_v[1] = 0;
	_v[2] = 0;
	_v[3] = 0;
}

Vec4::Vec4(float x, float y, float z, float w)
{
	_v[0] = x;
	_v[1] = y;
	_v[2] = z;
	_v[3] = w;
}

Vec4::Vec4(const Vec4 &src)
{
	_v[0] = src._v[0];
	_v[1] = src._v[1];
	_v[2] = src._v[2];
	_v[3] = src._v[3];
}

Vec4::~Vec4()
{

}

void	Vec4::print()
{
	std::cout << "<" << _v[0] << ", " << _v[1] << ", " << _v[2] << ", " << _v[3] << ">" << std::endl;
}

void	Vec4::setX(float x)
{
	_v[0] = x;
}

void	Vec4::setY(float y)
{
	_v[1] = y;
}

void	Vec4::setZ(float z)
{
	_v[2] = z;
}

void	Vec4::setW(float w)
{
	_v[3] = w;
}

Vec4	Vec4::operator-(const Vec4 &other)
{
	Vec4	res;
	res._v[0] = _v[0] - other._v[0];
	res._v[1] = _v[1] - other._v[2];
	res._v[2] = _v[2] - other._v[2];
	// Not sure about that?
	// TODO: check source
	res._v[3] = _v[3];
	// res._v[0] = _v[0] - other._v[0];
	return (res);
}

Vec4	Vec4::operator+(const Vec4 &other)
{
	Vec4	res;
	res._v[0] = _v[0] + other._v[0];
	res._v[1] = _v[1] + other._v[2];
	res._v[2] = _v[2] + other._v[2];
	// Not sure about that?
	// TODO: check source
	res._v[3] = _v[3];
	// res._v[0] = _v[0] - other._v[0];
	return (res);
}

Vec4	Vec4::operator*(const Vec4 &other)
{
	Vec4	res;
	res._v[0] = _v[0] * other._v[0];
	res._v[1] = _v[1] * other._v[2];
	res._v[2] = _v[2] * other._v[2];
	// Not sure about that?
	// TODO: check source
	res._v[3] = _v[3] * other._v[3];
	return (res);
}

Vec4	Vec4::operator=(const Vec4 &other)
{
	memcpy(_v, other._v, 4 * sizeof(float));
	return (*this);
}

float	Vec4::dot(Vec4 v)
{
	// TODO: check if w needs to be handled
	return (_v[0] * v._v[0] + _v[1] * v._v[1] + _v[2] * v._v[2]);
}

Vec4	Vec4::cross(Vec4 v)
{
	return Vec4(_v[1] * v._v[2] - _v[2] * v._v[1], _v[2] * v._v[0] - _v[0] * v._v[2], _v[0] * v._v[1] - _v[1] * v._v[0], _v[3]);
}

float Vec4::getNorm2()
{
	return _v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2];
}

void	Vec4::normalize()
{
	float	norm = sqrtf(getNorm2());
	_v[0] /= norm;
	_v[1] /= norm;
	_v[2] /= norm;
}

Vec4	Vec4::getNormalized()
{
	Vec4	res(*this);
	res.normalize();
	return (res);
}
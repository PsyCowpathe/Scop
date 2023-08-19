#include "Vector2.hpp"


//====================  CONSTRUCTORS  ====================

Vec2::Vec2()
{
	_d[0] = 0;
	_d[1] = 0;
}

Vec2::Vec2(const Vec2 &src)
{
	_d[0] = src._d[0];
	_d[1] = src._d[1];
}

Vec2::Vec2(float x, float y)
{
	_d[0] = x;
	_d[1] = y;
}

Vec2::~Vec2()
{

}


//====================  GETTER SETTER  ====================

void	Vec2::setX(float x)
{
	_d[0] = x;
}

void	Vec2::setY(float y)
{
	_d[1] = y;
}


//====================  OPERATORS  ====================

Vec2 Vec2::operator-(const Vec2 &t)
{
	Vec2 res;
	res._d[0] = _d[0] - t._d[0];
	res._d[1] = _d[1] - t._d[1];
	return res;
}

Vec2 Vec2::operator+(const Vec2 &t)
{
	Vec2 res;
	res._d[0] = _d[0] + t._d[0];
	res._d[1] = _d[1] + t._d[1];
	return res;
}

Vec2 Vec2::operator*(const Vec2 &t)
{
	Vec2 res;
	res._d[0] = _d[0] * t._d[0];
	res._d[1] = _d[1] * t._d[1];
	return res;
}

Vec2 Vec2::operator*(const float &t)
{
	Vec2 res;
	res._d[0] = _d[0] * t;
	res._d[1] = _d[1] * t;
	return res;
}

Vec2 &Vec2::operator=(const Vec2 &src)
{
	_d[0] = src._d[0];
	_d[1] = src._d[1];
	return *this;
}

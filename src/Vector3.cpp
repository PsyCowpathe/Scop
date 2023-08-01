#include "../headers/Vector3.hpp"

Vec3::Vec3()
{
	_d[0] = 0;
	_d[1] = 0;
	_d[2] = 0;
}

Vec3::Vec3(const Vec3 &src)
{
	_d[0] = src._d[0];
	_d[1] = src._d[1];
	_d[2] = src._d[2];
}

Vec3::Vec3(float x, float y, float z)
{
	_d[0] = x;
	_d[1] = y;
	_d[2] = z;
}

Vec3::~Vec3()
{
}

Vec3 Vec3::rotatex(float alpha)
{
	float y = _d[1] * cos(M_PI * alpha) - _d[2] * sin(M_PI * alpha);
	float z = _d[1] * sin(M_PI * alpha) + _d[2] * cos(M_PI * alpha);
	return (Vec3(_d[0], y, z));
}

Vec3 Vec3::rotatey(float beta)
{
	float x = _d[0] * cos(M_PI * beta) + _d[2] * sin(M_PI * beta);
	float z = _d[0] * -sin(M_PI * beta) + _d[2] * cos(M_PI * beta);
	return (Vec3(x, _d[1], z));
}

Vec3 Vec3::rotatez(float gamma)
{
	float x = _d[0] * cos(M_PI * gamma) - _d[1] * sin(M_PI * gamma);
	float y = _d[0] * sin(M_PI * gamma) + _d[1] * cos(M_PI * gamma);
	return (Vec3(x, y, _d[2]));
}

Vec3 Vec3::rotatexyz(Vec3 vec)
{
	Vec3 x = rotatex(vec._d[0]);
	Vec3 y = x.rotatey(vec._d[1]);
	return (y.rotatez(vec._d[2]));
}

void Vec3::setX(float x)
{
	_d[0] = x;
}

void Vec3::setY(float y)
{
	_d[1] = y;
}

void Vec3::setZ(float z)
{
	_d[2] = z;
}

Vec3 Vec3::operator-(const Vec3 &t)
{
	Vec3 res;
	res._d[0] = _d[0] - t._d[0];
	res._d[1] = _d[1] - t._d[1];
	res._d[2] = _d[2] - t._d[2];
	return res;
}

Vec3 Vec3::operator+(const Vec3 &t)
{
	Vec3 res;
	res._d[0] = _d[0] + t._d[0];
	res._d[1] = _d[1] + t._d[1];
	res._d[2] = _d[2] + t._d[2];
	return res;
}

Vec3 Vec3::operator*(const Vec3 &t)
{
	Vec3 res;
	res._d[0] = _d[0] * t._d[0];
	res._d[1] = _d[1] * t._d[1];
	res._d[2] = _d[2] * t._d[2];
	return res;
}

Vec3 Vec3::operator*(const float &t)
{
	Vec3 res;
	res._d[0] = _d[0] * t;
	res._d[1] = _d[1] * t;
	res._d[2] = _d[2] * t;
	return res;
}

float Vec3::dot(Vec3 v)
{
	return (_d[0] * v._d[0] + _d[1] * v._d[1] + _d[2] * v._d[2]);
}

float Vec3::getNorm2()
{
	return _d[0] * _d[0] + _d[1] * _d[1] + _d[2] * _d[2];
}

void Vec3::normalize()
{
	float norm = sqrt(getNorm2());
	_d[0] /= norm;
	_d[1] /= norm;
	_d[2] /= norm;
}

Vec3 Vec3::getNormalized()
{
	Vec3 res(*this);
	res.normalize();
	return res;
}

float Vec3::distance(const Vec3 &to)
{
	return (sqrt(pow(to._d[0] - _d[0], 2) + pow(to._d[1] - _d[1], 2) + pow(to._d[2] - _d[2], 2)));
}

Vec3 Vec3::cross(Vec3 v)
{
	return Vec3(_d[1] * v._d[2] - _d[2] * v._d[1], _d[2] * v._d[0] - _d[0] * v._d[2], _d[0] * v._d[1] - _d[1] * v._d[0]);
}

Vec3 &Vec3::operator=(const Vec3 &src)
{
	_d[0] = src._d[0];
	_d[1] = src._d[1];
	_d[2] = src._d[2];
	return *this;
}

void	Vec3::print()
{
	std::cout << "<" << _d[0] << ", " << _d[1] << ", " << _d[2] << ">" << std::endl;
}

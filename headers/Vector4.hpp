#pragma once
#include <math.h>
#include <iostream>
#include <string.h>

class Vec4
{
	private:
		float	_v[4];
		float	getNorm2();
	public:
		Vec4();
		Vec4(float x, float y, float z, float w);
		Vec4(const Vec4 &src);
		~Vec4();

		void		setX(float x);
		const float	&getX(void) const { return _v[0]; };

		void		setY(float y);
		const float	&getY(void) const { return _v[1]; };

		void		setZ(float z);
		const float	&getZ(void) const { return _v[2]; };

		void		setW(float w);
		const float&getW(void) const { return _v[3]; };

		Vec4		operator-(const Vec4 &other);
		Vec4		operator+(const Vec4 &other);
		Vec4		operator*(const Vec4 &other);
		Vec4		operator*(const float &x);
		Vec4		operator=(const Vec4 &other);

		void		print();

		float		dot(Vec4 v);
		Vec4		cross(Vec4 v);
		void		normalize();

		Vec4		getNormalized();
};


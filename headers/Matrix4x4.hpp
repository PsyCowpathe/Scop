#pragma once
#include <vector>
#include <iostream>
#include <string.h>
#include "Vector4.hpp"

class Matrix4
{
	private:
		float _m[16];
	public:
		Matrix4();
		Matrix4(float list[16]);
		~Matrix4();
		Matrix4	identity();
		Matrix4	perspective(float radians, float ratio, float z_near, float z_far);

		float	&operator[](size_t index);
		Matrix4	operator*(const Matrix4 &other);
		Vec4	operator*(const Vec4 &other);
		Matrix4	Matrix4::operator=(const Matrix4 &other);

		void	print();
};

float			angle_to_rad(float angle);
std::ostream	&operator<<(std::ostream &os, const Matrix4 &matrix);
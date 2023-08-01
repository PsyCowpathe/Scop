#pragma once
#include <vector>
#include <iostream>
#include <string.h>
#include "Vector4.hpp"

class Matrix4
{
	private:
	public:
		float _m[16];
		Matrix4();
		Matrix4(float list[16]);
		~Matrix4();
		Matrix4	identity();
		// Matrix4	perspective(float width, float height);
		Matrix4	perspective(float radians, float ratio, float z_near, float z_far);
		Matrix4	look_at(Vec4 eye, Vec4 center, Vec4 up);

		float	&operator[](size_t index);
		Matrix4	operator*(const Matrix4 &other);
		Vec4	operator*(const Vec4 &other);
		Matrix4	operator=(const Matrix4 &other);

		void	print();
};

float			angle_to_rad(float angle);
std::ostream	&operator<<(std::ostream &os, const Matrix4 &matrix);
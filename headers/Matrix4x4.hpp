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

		//==========  CONSTRUCTORS  ==========

		Matrix4();
		Matrix4(float list[16]);
		~Matrix4();

		//==========  MATRICES  ==========

		Matrix4		identity();
		Matrix4		translate(Vec4 to_add);
		Matrix4		rotation(char rotate, float angle);
		Matrix4		perspective(float radians, float ratio, float z_near, float z_far);
		Matrix4		look_at(Vec4 eye, Vec4 center, Vec4 up);

		//==========  UTILITY  ==========

		void	print();

		//==========  OPERATORS  ==========
		float	&operator[](size_t index);
		Matrix4	operator*(const Matrix4 &other);
		Vec4	operator*(const Vec4 &other);
		Matrix4	operator=(const Matrix4 &other);
		Matrix4	operator=(const float *other);

};

//==========  UTILITY  ==========
float			angle_to_rad(float angle);

//==========  OPERATORS  ==========
std::ostream	&operator<<(std::ostream &os, const Matrix4 &matrix);

#include <math.h>
#include <iostream>
#pragma once

class Vec4
{
	private:
		float	_v[4];
	public:
		Vec4(float x, float y, float z, float w);
		~Vec4();
		void	print();
};


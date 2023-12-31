#pragma once
#include <math.h>
#include <iostream>


class Vec2
{
	private:

	public:

		//==========  CONSTRUCTORS  ==========

		Vec2();
		Vec2(const Vec2 &src);
		Vec2(float x, float y);
		~Vec2();

		//==========  GETTER SETTER  ==========

		float			_d[2];
		void			setX(float x);
		const float		&getX(void) const { return _d[0]; };
		void			setY(float y);
		const float		&getY(void) const { return _d[1]; };

		//==========  OPERATORS  ==========

		Vec2			operator-(const Vec2 &);
		Vec2			operator+(const Vec2 &);
		Vec2			operator*(const Vec2 &);
		Vec2			operator*(const float &);
		Vec2			&operator=(const Vec2 &);
};

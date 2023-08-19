#include <math.h>
#include <iostream>

class Vec3
{
	private:
		float _d[3];

	public:

		//==========  CONSTRUCTORS  ==========

		Vec3();
		Vec3(const Vec3 &src);
		Vec3(float x, float y, float z);
		~Vec3();

		//==========  ALGEBRA  ==========
		
		Vec3			rotatex(float alpha);
		Vec3			rotatey(float beta);
		Vec3			rotatez(float gamma);
		Vec3			rotatexyz(Vec3 vec);
		float			getNorm2(void);
		void			normalize(void);
		Vec3			getNormalized(void);
		float			dot(Vec3 v);
		Vec3			cross(Vec3 v);
		float			distance(const Vec3 &to);

		//==========  GETTER SETTER  ==========

		void			setX(float x);
		const float		&getX(void) const { return _d[0]; };

		void			setY(float y);
		const float		&getY(void) const { return _d[1]; };

		void			setZ(float z);
		const float		&getZ(void) const { return _d[2]; };

		//==========  OPERATORS  ==========

		Vec3			operator-(const Vec3 &);
		Vec3			operator+(const Vec3 &);
		Vec3			operator*(const Vec3 &);
		Vec3			operator*(const float &);
		Vec3			&operator=(const Vec3 &);

		//==========  UTILITY  ==========
		
		void			print();
};

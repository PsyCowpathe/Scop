/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:02:09 by agirona           #+#    #+#             */
/*   Updated: 2023/08/03 16:14:57 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrice.hpp"

matrice::matrice()
{

}

matrice::~matrice()
{

}


//=================================  UTILS  ==================================


std::vector<float>		matrice::multiply_mm(std::vector<float> m1, std::vector<float> m2)
{
	std::vector<float>	result(16, 0);
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (i * j < 16)
	{
		j = 0;
		while (j < 4)
		{
			result[(4 * i) + j] = m1[4 * i] * m2[0 + j] + m1[4 * i + 1] * m2[4 + j]
				+ m1[4 * i + 2] * m2[8 + j] + m1[4 * i + 3] * m2[12 + j];
			j++;
		}
		i++;
	}
	return (result);
}

std::vector<float>		matrice::multiply_mv(std::vector<float> matrice, std::vector<float> vector)
{
	std::vector<float>	result(4, 0);
	int					i;

	i = 0;
	while (i < 4)
	{
		result[i] = (matrice[4 * i] * vector[0] + matrice[4 * i + 1] * vector[1]
				+ matrice[4 * i + 2] * vector[2] + matrice[4 * i + 3] * vector[3]);
		i++;
	}
	return (result);
}



//=================================  PROJECTION  ==================================


std::vector<float>		matrice::create_projection_matrice(float width, float height)
{
	float	ar = height / width;
	float	fov = 60 * (M_PI / 180);
	float	znear = 0.00001f;
	float	zfar = 1000.0f;
	float	proj[16] = {ar * (1 / tanf(fov / 2)), 0, 0, 0, 
						0, 1 / tanf(fov / 2), 0, 0,
						0, 0, zfar / (zfar - znear), (-zfar * znear) / (zfar - znear),
						0, 0, 1, 0};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		matrice[i] = proj[i];
		i++;
	}
	return (matrice);
}


//==================================  VIEW  ======================================


std::vector<float>		matrice::normalize(std::vector<float> v)
{
	float	norm;

	norm = sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
	v[0] /= norm;
	v[1] /= norm;
	v[2] /= norm;
	return (v);
}

std::vector<float>		matrice::cross(std::vector<float> v1, std::vector<float> v2)
{
	std::vector<float>	product(3, 0);

	product[0] = v1[1] * v2[2] - v1[2] * v2[1];
	product[1] = v1[2] * v2[0] - v1[0] * v2[2];
	product[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return (product);
}

float					matrice::dot(std::vector<float> v1, std::vector<float> v2)
{
	float	res;

	res = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	return (res);
}

std::vector<float>		matrice::create_view_matrice(std::vector<float> eye, std::vector<float> center,
														std::vector<float> up)
{
	std::vector<float>	vx(4, 0);
	std::vector<float>	vy(4, 0);
	std::vector<float>	vz(4, 0);
	std::vector<float>	matrice(16, 0);
	int					i;

	vz[0] = eye[0] - center[0];
	vz[1] = eye[1] - center[1];
	vz[2] = eye[2] - center[2];
	vz = normalize(vz);
	vy[0] = up[0];
	vy[1] = up[1];
	vy[2] = up[2];
	vx = cross(vy, vz);
	vy = cross(vz, vx);
	vx = normalize(vx);
	vy = normalize(vy);

	float    buff[16] =
	{
		vx[0], vy[0], vz[0], 0.0f,
		vx[1], vy[1], vz[1], 0.0f,
		vx[2], vy[2], vz[2], 0.0f,
		-(dot(vx, eye)), -(dot(vy, eye)), -(dot(vz,eye)), 1.0f
	};
	i = 0;
	while (i < 16)
	{
		matrice[i] = buff[i];
		i++;
	}
	return (matrice);
}


//==================================  ROTATE  =====================================

std::vector<float>		matrice::create_rotate_matrice(char rotate, float angle)
{
	float	rot_x[16] = {1, 0, 0, 0,
						0, cosf(angle), (sinf(angle) * -1), 0,
						0, sinf(angle), cosf(angle), 0,
						0, 0, 0, 1};
	float	rot_y[16] = {cosf(angle), 0, sinf(angle), 0,
						0, 1, 0, 0,
						sinf(angle) * -1, 0, cosf(angle), 0,
						0, 0, 0, 1};
	float	rot_z[16] = {cosf(angle), sinf(angle) * -1, 0, 0,
						sinf(angle), cosf(angle), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		if (rotate == 'x')
			matrice[i] = rot_x[i];
		else if (rotate == 'y')
			matrice[i] = rot_y[i];
		else if (rotate == 'z')
			matrice[i] = rot_z[i];
		i++;
	}
	return (matrice);
}


//==================================  SCALE  =====================================

std::vector<float>		matrice::create_scale_matrice(std::vector<float> factor)
{
	float	scale[16] = {factor[0], 0, 0, 0,
						0, factor[1], 0, 0,
						0, 0, factor[2], 0,
						0, 0, 0, 1};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		matrice[i] = scale[i];
		i++;
	}
	return (matrice);
}


//================================  TRANSLATE  ===================================

std::vector<float>		matrice::create_translate_matrice(std::vector<float> to_add)
{
	float	trans[16] = {1, 0, 0, to_add[0],
						0, 1, 0, to_add[1],
						0, 0, 1, to_add[2],
						0, 0, 0, 1};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		matrice[i] = trans[i];
		i++;
	}
	return (matrice);
}
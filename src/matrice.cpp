/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:02:09 by agirona           #+#    #+#             */
/*   Updated: 2023/08/01 18:28:30 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrice.hpp"

matrice::matrice()
{

}

matrice::~matrice()
{

}

std::vector<float>		matrice::perspective(float fov, float aspect, float znear, float zfar)
{
	float	rad = fov * (M_PI / 180.0);
	float	tan_half = tanf(rad / 2);
	
	float	perspective[16] = {
		1 / (aspect * tan_half), 0.0f, 0.0f, 0.0f,
		0.0f, 1 / tan_half, 0.0f, 0.0f,
		0.0f, 0.0f, (zfar + znear) / (zfar - znear), 1.0f,
		0.0f, 0.0f, 2 * (zfar * znear) / (zfar * znear), 0.0f
	};
	int	i = 0;
	std::vector<float>	matrice(16,0);
	while (i < 16)
	{
		matrice[i] = perspective[i];
		i++;
	}
	return (matrice);
}

std::vector<float>		matrice::look_at(std::vector<float> eye, std::vector<float> center, std::vector<float> up)
{
	std::vector<float>	added = {
		center[0] + eye[0],
		center[1] + eye[1],
		center[2] + eye[2],
	};
	std::vector<float>	f = normalize(added);
	std::vector<float>	u = normalize(up);
	std::vector<float>	s = normalize(cross(f, u));
	u = cross(s, f);

	std::vector<float>	res = {
		s[0], u[0], f[0], 0.0f,
		s[1], u[1], f[1], 0.0f,
		s[2], u[2], f[2], 0.0f,
		dot(s, eye), dot(u, eye), dot(f, eye), 1.0f
	};
	return (res);
}

std::vector<float>	matrice::cross(std::vector<float> v1, std::vector<float> v2)
{
	std::vector<float>	res = {
		v1[1] * v2[2] - v1[2] * v2[1],
		v1[2] * v2[0] - v1[0] * v2[2],
		v1[0] * v2[1] - v1[1] * v2[0]
	};
	return (res);
}

float	matrice::dot(std::vector<float> v1, std::vector<float> v2)
{
	float	prod = 0;
	for (int i = 0; i < 3; i++)
		prod = prod + v1[i] * v2[i];
	return (prod);
}

//=================================  PROJECTION  ==================================

std::vector<float>		matrice::create_projection_matrice(float width, float height)
{
	float	ar = width / height;
	float	znear = .1f;
	float	zfar = 10.0f;
	// float	fov = 90;
	float	alfFovRad = (90 / 2) * (M_PI / 180);
	float	zrange = znear - zfar;
	float	proj[16] = {1 / (ar * tanf(alfFovRad)), 0, 0, 0, 
						0, 1 / tanf(alfFovRad), 0, 0,
						0, 0, (-znear - zfar) / zrange, 2.0f * zfar * znear / zrange,
						0, 0, 1, 0};
	std::cout << "proj = " << proj[0] << std::endl;
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

std::vector<float>		matrice::project(std::vector<float> to_project, float width, float height)
{
	std::vector<float>	projected(4, 0);
	std::vector<float>	matrice;
	int					i;

	if (to_project.size() != 4)
		return (projected);
	i = 0;
	matrice = create_projection_matrice(width, height);
	while (i < 4)
	{
		projected[i] = (matrice[4 * i] * to_project[0] + matrice[4 * i + 1] * to_project[1]
				+ matrice[4 * i + 2] * to_project[2] + matrice[4 * i + 3] * to_project[3]);
		i++;
	}
	return (projected);
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

std::vector<float>		matrice::create_view_matrice(int pitch, int yaw)
{
	std::vector<float> 	dir(3, 0);
	std::vector<float> 	right(3, 0);
	std::vector<float> 	up(3, 0);
	
	dir[0] = cosf(yaw * (M_PI / 180)) * cosf(pitch * (M_PI / 180));
    dir[1] = sinf(pitch * (M_PI / 180));
    dir[2] = sinf(yaw * (M_PI / 180)) * cosf(pitch * (M_PI / 180));
	dir = normalize(dir);

	right[0] = cosf(yaw * (M_PI / 180)) - (M_PI / 2.0);
	right[1] = 0.0;
	right[2] = sinf(yaw * (M_PI / 180)) - (M_PI / 2.0);
	right = normalize(right);

	up[0] = dir[1] * right[2] - dir[2] * right[1];
	up[1] = dir[2] * right[0] - dir[0] * right[2];
	up[2] = dir[0] * right[1] - dir[1] * right[0];
	up = normalize(up);

	float	view[16] = {right[0], right[1], right[2], 0,
							up[0], up[1], up[2], 0,
							dir[0], dir[1], dir[2], 0,
							0, 0, 0, 1};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		matrice[i] = view[i];
		i++;
	}
	return (matrice);
}

std::vector<float>		matrice::view(std::vector<float> to_view, int pitch, int yaw)
{
	std::vector<float>	viewed(4, 0);
	std::vector<float>	matrice;
	int					i;

	if (to_view.size() != 4)
		return (viewed);
	i = 0;
	matrice = create_view_matrice(pitch, yaw);
	while (i < 4)
	{
		viewed[i] = (matrice[4 * i] * to_view[0] + matrice[4 * i + 1] * to_view[1]
				+ matrice[4 * i + 2] * to_view[2] + matrice[4 * i + 3] * to_view[3]);
		i++;
	}
	return (viewed);

}


//==================================  ROTATE  =====================================

std::vector<float>		matrice::create_rotate_matrice(char rotate, float angle)
{
	float	rot_x[16] = {1, 0, 0, 0, 0, cosf(angle), (sinf(angle) * -1), 0, 0, sinf(angle), cosf(angle), 0, 0, 0, 0, 0};
	float	rot_y[16] = {cosf(angle), 0, sinf(angle), 0, 0, 1, 0, 0, sinf(angle) * -1, 0, cosf(angle), 0, 0, 0, 0, 0};
	float	rot_z[16] = {cosf(angle), sinf(angle) * -1, 0, 0, sinf(angle), cosf(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
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

std::vector<float>		matrice::rotate(std::vector<float> to_rotate, float angle, char rotate)
{
	std::vector<float>	rotated(4, 0);
	std::vector<float>	matrice;
	int					i;

	if (to_rotate.size() != 4 || angle < 0 || angle > 360)
		return (rotated);
	i = 0;
	matrice = create_rotate_matrice(rotate, angle *= (M_PI / 180));
	while (i < 4)
	{
		rotated[i] = (matrice[4 * i] * to_rotate[0] + matrice[4 * i + 1] * to_rotate[1]
				+ matrice[4 * i + 2] * to_rotate[2] + matrice[4 * i + 3] * to_rotate[3]);
		i++;
	}
	return (rotated);
}



//==================================  SCALE  =====================================

std::vector<float>		matrice::create_scale_matrice(std::vector<float> factor)
{
	float	scale[16] = {factor[0], 0, 0, 0, 0, factor[1], 0, 0, 0, 0, factor[2], 0, 0, 0, 0, 1};
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

std::vector<float>		matrice::scale(std::vector<float> to_scale, std::vector<float> factor)
{
	std::vector<float>	scaled(4, 0);
	std::vector<float>	matrice;
	int					i;

	if (to_scale.size() != 4 || factor.size() != 4)
		return (scaled);
	i = 0;
	matrice = create_scale_matrice(factor);
	while (i < 4)
	{
		scaled[i] = matrice[4 * i] * to_scale[0] + matrice[4 * i + 1] * to_scale[1]
				+ matrice[4 * i + 2] * to_scale[2] + matrice[4 * i + 3] * to_scale[3];
		i++;
	}
	return (scaled);
}



//================================  TRANSLATE  ===================================

std::vector<float>		matrice::create_translate_matrice(std::vector<float> to_add)
{
	float	trans[16] = {1, 0, 0, to_add[0], 0, 1, 0, to_add[1], 0, 0, 1, to_add[2], 0, 0, 0, 1};
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

std::vector<float>		matrice::translate(std::vector<float> to_translate, std::vector<float> to_add)
{
	std::vector<float>	translated(4, 0);
	std::vector<float>	matrice;

	if (to_add.size() != 4 || to_translate.size() != 4)
		return (translated);
	std::cout << "tanslate" << std::endl;
	matrice = create_translate_matrice(to_add);
	translated[0] = matrice[3] + to_translate[0];
	translated[1] = matrice[7] + to_translate[1];
	translated[2] = matrice[11] + to_translate[2];
	translated[3] =	matrice[15] + to_translate[3];
	return (translated);
}

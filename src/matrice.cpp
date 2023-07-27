/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:02:09 by agirona           #+#    #+#             */
/*   Updated: 2023/07/27 13:41:49 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrice.hpp"

matrice::matrice()
{

}

matrice::~matrice()
{

}


//=================================  PROJECTION  ==================================

std::vector<float>		matrice::create_projection_matrice(float width, float height)
{
	float	ar = width / height;
	float	znear = 1.0f;
	float	zfar = 10.0f;
	float	fov = 90;
	float	zrange = znear - zfar;
	float	proj[16] = {1 / (ar * tanf((fov / 2) * (M_PI / 180))), 0, 0, 0, 
						0, 1 / (tanf((fov / 2) * M_PI / 180)), 0, 0,
						0, 0, (-znear - zfar) / zrange, 2.0f * zfar * znear / zrange,
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

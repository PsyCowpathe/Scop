/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:02:09 by agirona           #+#    #+#             */
/*   Updated: 2023/07/24 20:43:09 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrice.hpp"

matrice::matrice()
{

}

matrice::~matrice()
{

}

//==================================  ROTATE  =====================================

std::vector<float>		matrice::create_rotate_matrice(char rotate, float angle)
{
	float	rot_x[9] = {1, 0, 0, 0, cosf(angle), (sinf(angle) * -1), 0, sinf(angle), cosf(angle)};
	float	rot_y[9] = {cosf(angle), 0, sinf(angle), 0, 1, 0, sinf(angle) * -1, 0, cosf(angle)};
	float	rot_z[9] = {cosf(angle), sinf(angle) * -1, 0, sinf(angle), cosf(angle), 0, 0, 0, 1};
	std::vector<float>	matrice(9);
	int					i;

	i = 0;
	while (i < 9)
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
	std::vector<float>	rotated(3);
	std::vector<float>	matrice;
	int					i;

	if (to_rotate.size() != 3 || angle < 0 || angle > 360)
		return (rotated);
	i = 0;
	matrice = create_rotate_matrice(rotate, angle *= (M_PI / 180));
	while (i < 3)
	{
		rotated[i] = (matrice[3 * i] * to_rotate[0] + matrice[3 * i + 1] * to_rotate[1]
				+ matrice[3 * i + 2] * to_rotate[2]);
		i++;
	}
	return (rotated);
}



//==================================  SCALE  =====================================

std::vector<float>		matrice::create_scale_matrice(std::vector<float> factor)
{
	float	scale[16] = {factor[0], 0, 0, 0, 0, factor[1], 0, 0, 0, 0, factor[2], 0, 0, 0, 0, 1};
	std::vector<float>	matrice(9);
	int					i;

	i = 0;
	while (i < 9)
	{
		matrice[i] = scale[i];
		i++;
	}
	return (matrice);
}

std::vector<float>		matrice::scale(std::vector<float> to_scale, std::vector<float> factor)
{
	std::vector<float>	scaled(3);
	std::vector<float>	matrice;
	int					i;

	if (to_scale.size() != 3 || factor.size() != 3)
		return (scaled);
	i = 0;
	matrice = create_scale_matrice(factor);
	while (i < 3)
	{
		scaled[i] = matrice[3 * i] * to_scale[0] + matrice[3 * i + 1] * to_scale[1]
				+ matrice[3 * i + 2] * to_scale[2];// + matrice[4 * i + 3] * to_scale[3];
		i++;
	}
	return (scaled);
}



//================================  TRANSLATE  ===================================

std::vector<float>		matrice::create_translate_matrice(std::vector<float> to_add)
{
	float	trans[16] = {1, 0, 0, to_add[0], 0, 1, 0, to_add[1], 0, 0, 1, to_add[2], 0, 0, 0, 1};
	std::vector<float>	matrice(16);
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
	std::vector<float>	translated(3);
	std::vector<float>	matrice;

	if (to_add.size() != 3 || to_translate.size() != 3)
		return (translated);
	matrice = create_translate_matrice(to_add);
	translated[0] = matrice[3] + to_translate[0];
	translated[1] = matrice[7] + to_translate[1];
	translated[2] = matrice[11] + to_translate[2];// + matrice[4 * i + 3] * to_translate[3];
	return (translated);

}



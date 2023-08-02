/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:00:33 by agirona           #+#    #+#             */
/*   Updated: 2023/08/02 16:03:06 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICE_HPP
# define MATRICE_HPP

# include <iostream>
# include <vector>
# include <math.h>

class matrice
{
	public :

		matrice();
		~matrice();
		//std::vector<float>	view(std::vector<float> to_view, float pitch, float yaw);
		std::vector<float>	view(std::vector<float> view, std::vector<float> eye, std::vector<float> center, std::vector<float> up);
		std::vector<float>	project(std::vector<float> to_project, float width, float height);
		std::vector<float>	rotate(std::vector<float> to_rotate, float angle, char rotate);
		std::vector<float>	translate(std::vector<float> to_translate, std::vector<float> to_add);
		std::vector<float>	scale(std::vector<float> to_scale, std::vector<float> factor);

		std::vector<float>	multiply_mm(std::vector<float> m1, std::vector<float> m2);
		std::vector<float>	multiply_mv(std::vector<float> matrice, std::vector<float> vector);

std::vector<float>			camera(std::vector<float> U, std::vector<float> V, std::vector<float> N, std::vector<float> CameraPos, std::vector<float> to_view);

	//private :

		std::vector<float>	cross(std::vector<float> v1, std::vector<float> v2);
		float				dot(std::vector<float> v1, std::vector<float> v2);


std::vector<float>			create_camera_matrice(std::vector<float> U, std::vector<float> V, std::vector<float> N, std::vector<float> CameraPos);

		std::vector<float>	create_projection_matrice(float width, float height);
		std::vector<float>	create_rotate_matrice(char rotate, float angle);
		std::vector<float>	create_scale_matrice(std::vector<float> factor);
		std::vector<float>	create_translate_matrice(std::vector<float> to_add);
		//std::vector<float>	create_view_matrice(float pitch, float yaw);
		std::vector<float>	create_view_matrice(std::vector<float> eye, std::vector<float> center, std::vector<float> up);
		std::vector<float>	normalize(std::vector<float> v);
};

#endif

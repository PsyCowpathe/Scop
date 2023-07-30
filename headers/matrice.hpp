/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:00:33 by agirona           #+#    #+#             */
/*   Updated: 2023/07/27 19:42:56 by agirona          ###   ########.fr       */
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

		std::vector<float>	view(std::vector<float> to_view, int pitch, int yaw);
		std::vector<float>	project(std::vector<float> to_project, float width, float height);
		std::vector<float>	rotate(std::vector<float> to_rotate, float angle, char rotate);
		std::vector<float>	translate(std::vector<float> to_translate, std::vector<float> to_add);
		std::vector<float>	scale(std::vector<float> to_scale, std::vector<float> factor);

	private :

		std::vector<float>	create_projection_matrice(float width, float height);
		std::vector<float>	create_rotate_matrice(char rotate, float angle);
		std::vector<float>	create_scale_matrice(std::vector<float> factor);
		std::vector<float>	create_translate_matrice(std::vector<float> to_add);
		std::vector<float>	create_view_matrice(int pitch, int yaw);
		std::vector<float>	normalize(std::vector<float> v);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:00:33 by agirona           #+#    #+#             */
/*   Updated: 2023/08/03 13:45:53 by agirona          ###   ########.fr       */
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
		std::vector<float>	multiply_mm(std::vector<float> m1, std::vector<float> m2);
		std::vector<float>	multiply_mv(std::vector<float> matrice, std::vector<float> vector);
		std::vector<float>	create_projection_matrice(float width, float height);
		std::vector<float>	create_view_matrice(std::vector<float> eye, std::vector<float> center, std::vector<float> up);
		std::vector<float>	create_rotate_matrice(char rotate, float angle);
		std::vector<float>	create_scale_matrice(std::vector<float> factor);
		std::vector<float>	create_translate_matrice(std::vector<float> to_add);


	private :

		std::vector<float>	cross(std::vector<float> v1, std::vector<float> v2);
		float				dot(std::vector<float> v1, std::vector<float> v2);
		std::vector<float>	normalize(std::vector<float> v);
};

#endif

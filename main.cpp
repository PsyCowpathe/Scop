/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:31:20 by agirona           #+#    #+#             */
/*   Updated: 2023/07/19 19:45:29 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.hpp"

int		main(void)
{
	render	test(4, 3, 3, 640, 480, "GLFW BUT IN A CLASS !");
	static const GLfloat vertex_buffer[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	std::cout << sizeof(vertex_buffer) << std::endl;
	test.draw_triangle(vertex_buffer);
	return (0);
}
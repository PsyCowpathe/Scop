/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:31:20 by agirona           #+#    #+#             */
/*   Updated: 2023/08/03 16:09:28 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/render.hpp"

int		main(void)
{
	std::vector<float>			vertices;
	std::vector<float>			uv;
	std::vector<float>			normals;
	std::vector<unsigned int>	faces;

	load_object("objects/cube.obj", vertices, uv, normals, faces);

	render	test(4, 3, 3, 640, 480, "GLFW BUT IN A CLASS !");
	/*static const GLfloat vertex_buffer[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
	};*/

	/*static const GLfloat vertex_buffer[] =
	{
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};*/

	test.draw_triangle(vertices, faces, uv);
	std::cout << "Program end" << std::endl;
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:31:20 by agirona           #+#    #+#             */
/*   Updated: 2023/08/15 15:33:20 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.hpp"
#include "object_loader.hpp"

int		main(void)
{
	std::vector<float>			vertices;
	std::vector<float>			uv;
	std::vector<float>			normals;
	std::vector<unsigned int>	faces;
	std::vector<unsigned int>	uv_indices;

	load_object("objects/ball.obj", vertices, uv, normals, faces, uv_indices);

	render	test(4, 3, 3, 640, 480, "GLFW BUT IN A CLASS !", faces);
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

	test.loop(vertices, faces, uv, uv_indices);
	std::cout << "Program end" << std::endl;
	return (0);
}

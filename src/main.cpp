/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:31:20 by agirona           #+#    #+#             */
/*   Updated: 2023/07/26 18:33:45 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/render.hpp"
#include "../headers/loadObject.hpp"

int		main(void)
{
	std::vector<vec3>	vertices;
	std::vector<vec2>	uv;
	std::vector<vec3>	normals;
	loadObject("objects/cube.obj", vertices, uv, normals);
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

	static const GLfloat vertex_buffer[] =
	{
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};


	test.draw_triangle(vertex_buffer);
	return (0);
}

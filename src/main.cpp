/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:31:20 by agirona           #+#    #+#             */
/*   Updated: 2023/08/01 14:06:10 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/render.hpp"
#include "../headers/loadObject.hpp"

int		main(void)
{
	std::vector<float>	vertices;
	std::vector<float>	uv;
	std::vector<float>	normals;
	std::vector<unsigned int>	faces;
	float	mat_m[16] = {
		10, 12, 46, 2,
		89, 23, 1, 39,
		30, 39, 1, 30,
		89, 99, 23, 67
	};
	Matrix4	mat(mat_m);
	Vec4	m_test(10, 12, 2, 0);

	m_test.print();
	m_test =  mat * m_test;
	// mat.print();
	m_test.print();
	exit(0);
	loadObject("objects/cube.obj", vertices, uv, normals, faces);
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
	test.draw_triangle(vertices, faces);
	return (0);
}

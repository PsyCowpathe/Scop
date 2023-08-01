/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:31:20 by agirona           #+#    #+#             */
/*   Updated: 2023/08/01 16:32:28 by ckurt            ###   ########lyon.fr   */
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
		3, 4, 1, 0,
		4, 5, 1, 3,
		1, 4, 6, 4,
		9, 9, 5, 7
	};
	float	mat_m2[16] = {
		1, 2, 5, 9,
		2, 3, 1, 1,
		4, 5, 0, 9,
		1, 3, 4, 1
	};
	Matrix4	mat(mat_m);
	Matrix4	mat2(mat_m2);
	Vec4	m_test(10, 12, 2, 0);

	// m_test.print();
	m_test =  mat * m_test;
	mat.print();
	mat = mat * mat2;
	mat.print();
	// m_test.print();
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

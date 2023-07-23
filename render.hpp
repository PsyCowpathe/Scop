/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:18 by agirona           #+#    #+#             */
/*   Updated: 2023/07/23 16:18:36 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_HPP
# define RENDER_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

class render
{
	private :

		GLFWwindow		*_window;
		GLuint			_vertexArrayID;
		GLuint			_vertexBuffer;
		char			_rotate_axis = 'x';

		int				glfw_init();
		void			set_hint(int aliasing, float openGL_min, float openGL_max);
		int				create_window(int width, int height, std::string name);
		void			clear();
		void			set_callback();
		void			set_context();
		static void		error_callback(int error, const char *description); //chelou le static, a voir
		static void		key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void			change_rotate_axis(int key);
		int				glew_init();
		void			create_vertex_array();
		float			*create_rotate_matrice(char rotate, float angle);

	public :

		render(int aliasing, float openGl_min, float openGl_max, int width, int height, std::string name);
		~render();
		void	draw_triangle(const GLfloat vertex_buffer[]);
		std::vector<float>	rotate(std::vector<float> vertex, float angle, char rotate);
};

#endif

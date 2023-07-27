/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:18 by agirona           #+#    #+#             */
/*   Updated: 2023/07/27 18:49:27 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_HPP
# define RENDER_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include "matrice.hpp"

#include "pseudoVec3.hpp"

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

class render
{
	private :

		GLFWwindow		*_window;
		GLuint			_vertexArrayID;
		GLuint			_vertexBuffer;
		char			_rotate_axis = 'x';
		matrice			matrice;
		int				_width;
		int				_height;
		int				_pitch = 0;
		int				_yaw = -90;

		//GLfloat			*_current_vertex;
		// const GLfloat	*_original_vertex;

		int				glfw_init();
		void			set_hint(int aliasing, float openGL_min, float openGL_max);
		int				create_window(std::string name);
		void			clear();
		void			set_callback();
		void			set_context();
		static void		error_callback(int error, const char *description);
		static void		key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void			change_rotate_axis(int key);
		int				glew_init();
		void			create_vertex_array();

		float			*make_mega_float(std::vector<float> vertices, std::vector<unsigned int> faces);
		float			*make_perspective(float *mega_float, int size);

	public :

		render(int aliasing, float openGl_min, float openGl_max, int width, int height, std::string name);
		~render();
		//void	draw_triangle(const GLfloat vertex_buffer[]);
		void	draw_triangle(std::vector<float>	vertices, std::vector<unsigned int>	faces);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:18 by agirona           #+#    #+#             */
/*   Updated: 2023/08/03 18:28:09 by agirona          ###   ########.fr       */
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
#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

// #include "./glm/glm/glm.hpp"
// #include "./glm/glm/gtx/transform.hpp"
// #include "./glm/glm/gtx/string_cast.hpp"

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

class render
{
	private :

		GLFWwindow		*_window;
		GLuint			_vertexArrayID;
		GLuint			_vertexBuffer;
		GLuint			_colorBuffer;
		
		char			_rotate_axis = 'x';
		int				_moov_x = 0;
		int				_moov_y = 0;
		int				_moov_z = 0;
		matrice			matrice;
		int				_width;
		int				_height;
		// float			_pitch = 0;
		// float			_yaw = -90;

		//GLfloat			*_current_vertex;
		// const GLfloat	*_original_vertex;

		//Init
		
		int				create_window(std::string name);
		int				glfw_init();
		int				glew_init();

		//Config

		void			set_hint(int aliasing, float openGL_min, float openGL_max);
		void			set_callback();
		void			set_context();

		//Callback
		static void		error_callback(int error, const char *description);
		static void		key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void			change_rotate_axis(int key);
		void			moov_object(int key);

		//Utils
		void			create_vertex_array();

		void			clear();
		float			*make_mega_float(std::vector<float> vertices, std::vector<unsigned int> faces);

	public :

		render(int aliasing, float openGl_min, float openGl_max, int width, int height, std::string name);
		~render();
		void	draw_triangle(std::vector<float>	vertices, std::vector<unsigned int>	faces);//
};

#endif

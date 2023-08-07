/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:18 by agirona           #+#    #+#             */
/*   Updated: 2023/08/04 19:33:01 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_HPP
# define RENDER_HPP

#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <vector>
#include <map>
#include <chrono>
#include "matrice.hpp"
#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include "load_object.hpp"
#include "Texture.hpp"

// #include "./glm/glm/glm.hpp"
// #include "./glm/glm/gtx/transform.hpp"
// #include "./glm/glm/gtx/string_cast.hpp"

GLuint load_shaders(const char * vertex_file_path, const char * fragment_file_path);

class render
{
	private :

		GLFWwindow		*_window;
		GLuint			_vertexArrayID;
		GLuint			_vertexBuffer;
		GLuint			_colorBuffer;
		GLuint			_texBuffer;
		
		char			_rotate_axis = 'y';
		float					_moov_x = 0;
		float					_moov_y = 0;
		float					_moov_z = 0;
		matrice					matrice;
		int						_width;
		int						_height;
		std::map<int, bool>		_keys;
		bool			_t_mode = 0;
		
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
		static void		resize_callback(GLFWwindow *win, int width, int height);
		void			handle_inputs();
		void			change_rotate_axis(int key);
		void			change_color(int key);

		//Texture
		void			switch_texture();

		//Utils
		void			create_vertex_array();

		float			*make_mega_float(std::vector<float> vertices, std::vector<unsigned int> faces);
		Vec4			check_moov(Vec4 factor);

		void			key_print();
		
		//Uniforms location pointers
		GLuint			_color;

	public :

		void			clear();
		GLuint			_pixels;
		render(int aliasing, float openGl_min, float openGl_max, int width, int height, std::string name);
		~render();
		void			draw_triangle(std::vector<float>	vertices, std::vector<unsigned int>	faces, std::vector<float> uv);//
};

#endif

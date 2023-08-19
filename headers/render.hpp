/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:18 by agirona           #+#    #+#             */
/*   Updated: 2023/08/19 18:59:55 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_HPP
# define RENDER_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "object_loader.hpp"
#include "text.hpp"
#include "object_loader.hpp"
#include "Texture.hpp"

class Texture;

class render
{
	private :

		//++++++++++  VARIABLES  ++++++++++
		//==========  ENGINE  ==========

		GLFWwindow					*_window;
		GLuint						_vertexArrayID;
		GLuint						_vertexBuffer;
		GLuint						_colorBuffer;
		GLuint						_texBuffer;
		GLuint						_programID;
		int							_width;
		int							_height;
		bool						_wireframe = false;
		int							_frames = 0;
		float						_delta_time = 0;
		bool						_fullscreen = false;
		bool						_is_fullscreen = false;
		int							_win_pos[2];
		int							_win_dim[2];
		float						_angle = 0;
		GLuint						_color;
		Texture						*_p_tex = NULL;



		//==========  PARSING RESULTS  ==========
		
		std::vector<float>			_vertices;
		std::vector<unsigned int>	_vert_indices;
		std::vector<float>			_uv;
		std::vector<unsigned int>	_uv_indices;
		std::vector<float>			_normals;
		std::vector<unsigned int>	_normals_indices;

		//==========  KEY handling  ==========

		std::map<int, bool>			_keys;

		char						_rotate_axis = 'y';
		char						_random_axis = 'y';
		bool						_spins = true;
		bool						_changed = 0;

		Vec4						_factor;
		float						_moov_x = 0;
		float						_moov_y = 0;
		float						_moov_z = 0;
		float						_accelerate = 0;

		bool						_t_mode;
		int							_s_mod;

		//==========  UI  ==========

		std::stringstream			_ui_fps;
		std::string					_model_name;
		bool						_debug_mode = false;



		//++++++++++  FUNCTIONS  ++++++++++
		
		//==========  INIT  ==========
		
		int				create_window(std::string name);
		int				glfw_init();
		int				glew_init();
		void			create_vertex_array();

		//==========  CONFIG  ==========

		void			set_hint(int aliasing, float openGL_min, float openGL_max);
		void			set_callback();
		void			set_context();

		//==========  ENGINE  ==========

		void			update(float *transformed_vertices);
		void			draw();
		void			get_fps(float &last_time);
		void			printUI();
		void			toggle_fullscreen(std::string name);

		//==========  CALLBACK  ==========

		static void		error_callback(int error, const char *description);
		static void		key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void		resize_callback(GLFWwindow *win, int width, int height);
		void			handle_inputs();

		//==========  UTILS  ==========

		float    		*make_tex_mega_float(std::vector<float> uv, std::vector<unsigned int> uv_indices);
		float			*make_mega_float(std::vector<float> vertices, std::vector<unsigned int> faces);
		void			to_center(float *result, size_t size);
		Vec4			check_moov(Vec4 factor);
		void			switch_texture();
		
	public :

		GLuint			_pixels;

		//==========  CONSTRUCTORS  ==========
		
		render(int aliasing, float openGl_min, float openGl_max, int width, int height,
				std::string name, std::string obj_path, bool fullscreen);
		~render();

		//==========  ENGINE  ==========

		void	loop();

		//==========  UTILS  ==========

		void			clear();
};

#endif

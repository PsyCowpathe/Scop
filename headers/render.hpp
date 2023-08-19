/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:18 by agirona           #+#    #+#             */
/*   Updated: 2023/08/19 15:43:15 by agirona          ###   ########.fr       */
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
#include <chrono>
#include <sstream>
#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "object_loader.hpp"
#include "text.hpp"

#include "object_loader.hpp"
#include "Texture.hpp"

// #include "./glm/glm/glm.hpp"
// #include "./glm/glm/gtx/transform.hpp"
// #include "./glm/glm/gtx/string_cast.hpp"

GLuint load_shaders(const char * vertex_file_path, const char * fragment_file_path);

class render
{
	private :
		GLFWwindow					*_window;
		GLuint						_vertexArrayID;
		GLuint						_vertexBuffer;
		GLuint						_colorBuffer;
		GLuint						_texBuffer;

		// Parsed info
		std::vector<float>			_vertices;
		std::vector<unsigned int>	_vert_indices;
		std::vector<float>			_uv;
		std::vector<unsigned int>	_uv_indices;
		std::vector<float>			_normals;
		std::vector<unsigned int>	_normals_indices;

		char						_rotate_axis = 'y';
		float						_moov_x = 0;
		float						_moov_y = 0;
		float						_moov_z = 0;
		float						_angle = 0;
		Vec4						_factor;
		float						_delta_time = 0;
		int							_width;
		int							_height;
		bool						_wireframe = false;
		bool						_spins = true;
		std::map<int, bool>			_keys;
		GLuint						_programID;
		bool						_t_mode;
		int							_s_mod;
		int							_frames = 0;
		bool						_fullscreen = false;
		bool						_is_fullscreen = false;
		int							_win_pos[2];
		int							_win_dim[2];
		bool						_changed = 0;
		char						_random_axis = 'y';
		float						_accelerate = 0;

		// UI
		std::stringstream			_ui_fps;
		std::string					_model_name;
		bool						_debug_mode = false;

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
		void			change_color(int key);

		//Texture
		void			switch_texture();
		void			update(float *transformed_vertices);
		void			draw();
		void			get_fps(float &last_time);


		//Utils
		void			create_vertex_array();

		float    		*make_tex_mega_float(std::vector<float> uv, std::vector<unsigned int> uv_indices);
		float			*make_mega_float(std::vector<float> vertices, std::vector<unsigned int> faces);
		Vec4			check_moov(Vec4 factor);
		void			to_center(float *result, size_t size);

		void			key_print();
		void			printUI();
		
		//Uniforms location pointers
		GLuint			_color;
		void			toggle_fullscreen(std::string name);

	public :
		void			clear();
		GLuint			_pixels;
		render(int aliasing, float openGl_min, float openGl_max, int width, int height, std::string name, std::string obj_path, bool fullscreen);
		~render();
		void	loop();
};

#endif

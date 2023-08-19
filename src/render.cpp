/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:26:34 by agirona           #+#    #+#             */
/*   Updated: 2023/08/19 19:01:22 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.hpp"

//====================  CONSTRUCTORS  ====================

render::render(int aliasing, float openGL_min, float openGL_max, int width, int height, std::string name, std::string obj_path, bool fullscreen)
{
	_fullscreen = fullscreen;
	size_t	find = obj_path.find_last_of('/');
	_model_name = "default";
	if (find != std::string::npos && obj_path.length() != 1)
		_model_name = obj_path.substr(find + 1, obj_path.find_last_of('.') - find - 1);
	std::cout << "name: " << _model_name << std::endl;
	_s_mod = 0;
	load_object(obj_path.c_str(), _vertices, _uv, _normals, _vert_indices, _uv_indices);
	_factor = Vec4(0, 0, 0, 0);
	if (width < 0 || height < 0)
		clear();
	_width = width;
	_height = height;
	if (glfw_init() == -1)
		clear();
	set_hint(aliasing, openGL_min, openGL_max);
	
	if (create_window(name) == -1)
		clear();

	set_callback();
	set_context();
	glfwSwapInterval(1);
	if (glew_init() == -1)
		clear();
	_programID = load_shaders("shader/vertex_shader.vert", "shader/frag_shader.frag");

	// Init VAO
	create_vertex_array();

	// Define viewport dimensions
	glViewport(0, 0, _width, _height);

	// Enable/init depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Add culling (1st line culls backfaces by default, so 2nd line is optionnal ?)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

render::~render()
{
	std::cout << "destruction" << std::endl;
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(1, &_vertexArrayID);
	glDeleteBuffers(1, &_colorBuffer);
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_texBuffer);
	glfwDestroyWindow(_window);
	glfwTerminate();
}


//====================  INIT  ====================

int		render::create_window(std::string name)
{
	_window = glfwCreateWindow(_width, _height, name.c_str(), NULL , NULL);
	_is_fullscreen = false;
	if (!_window)
	{
		std::cout << "GLFW window creation failed :(" << std::endl;
		return (-1);
	}
	return (1);
}


int		render::glfw_init()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init failed :(" << std::endl;
		return (-1);
	}
	return (1);
}

int		render::glew_init()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew init failed :(" << std::endl;
		return (-1);
	}
	return (1);
}

void	render::create_vertex_array()
{
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);
}


//====================  CONFIG  ====================

void	render::set_hint(int aliasing, float openGL_min, float openGL_max)
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_SAMPLES, aliasing);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGL_min);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGL_max);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
}

void	render::set_context()
{
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);
	glewExperimental = true;
}

void	render::set_callback()
{
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(_window, key_callback);
	glfwSetWindowSizeCallback(_window, resize_callback);
}


//====================  ENGINE  ====================

void	render::loop()
{
	std::vector<float>		tmp;
	std::vector<float>		vertex(4);
	float					*transformed_vertices = make_mega_float(_vertices, _vert_indices);
	float					*transformed_uv = make_tex_mega_float(_uv, _uv_indices);
	
	// ************
	// * VERTICES *
	// ************

	glEnableVertexAttribArray(0);
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*transformed_vertices) * (_vert_indices.size() * 3), transformed_vertices, GL_STATIC_DRAW); 
	this->_color = glGetUniformLocation(_programID, "u_color");
	glUniform3f(this->_color, 1.0f, 1.0f, 1.0f);

	// ************
	// * TEXTURES *
	// ************

		_p_tex = new Texture(GL_TEXTURE_2D, "objects/textures/moon_color.bmp", this);
		_p_tex->load_tex();

		GLuint gSamplerLocation = glGetUniformLocation(_programID, "gSampler");
		if (gSamplerLocation == 0)
		{
			std::cout << "Error getting uniform location of 'gSampler'" << std::endl;
    		clear();
    	}
	glUniform1i(gSamplerLocation, 0);
	glUseProgram(_programID);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &_texBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _texBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*transformed_uv) * (_uv_indices.size() * 2), transformed_uv, GL_STATIC_DRAW);
	delete[] transformed_uv;
	glVertexAttribPointer
		(
		 1,				// attribute 0. No particular reason for 0, but must match the layout in the shader.
		 2,				// size (here we have 2 values per vertex)
		 GL_FLOAT,		// type
		 GL_FALSE,		// normalized?
		 0,				// stride (y-a-t il un ecart entre les donnes de chaque vertice dans l'array ?)
		 (void*)0		// array buffer offset (at beginning of array)
		);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	initText("fonts/mono2.dds");
	float	last_time = glfwGetTime();
	_ui_fps << "fps: loading..." << std::endl;

	// ***************
	// * RENDER LOOP *
	// ***************

	while (!glfwWindowShouldClose(_window))
	{
		glUseProgram(_programID);
		get_fps(last_time);
		handle_inputs();
		update(transformed_vertices);
		draw();
	}
	delete[] transformed_vertices;
}

void	render::draw()
{
	glBindTexture(GL_TEXTURE_2D, _p_tex->_texture_obj);
	glClearColor(.2, .2, .2, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer
		(
		 0,				// attribute 0. No particular reason for 0, but must match the layout in the shader.
		 3,				// size (here we have 3 values per vertex)
		 GL_FLOAT,		// type
		 GL_FALSE,		// normalized?
		 0,				// stride (y-a-t il un ecart entre les donnes de chaque vertice dans l'array ?)
		 (void*)0		// array buffer offset (at beginning of array)
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _texBuffer);
	glVertexAttribPointer
		(
		 1,				// attribute 0. No particular reason for 0, but must match the layout in the shader.
		 2,				// size (here we have 2 values per vertex)
		 GL_FLOAT,		// type
		 GL_FALSE,		// normalized?
		 0,				// stride (y-a-t il un ecart entre les donnes de chaque vertice dans l'array ?)
		 (void*)0		// array buffer offset (at beginning of array)
		);

	glDrawArrays(GL_TRIANGLES, 0, _vert_indices.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	if (_debug_mode)
		printUI();
	glfwSwapBuffers(_window);
	glfwSetWindowUserPointer(_window, this);
	glfwPollEvents();
	glFinish();
}

void	render::update(float *transformed_vertices)
{


	if (_changed == 1)
	{
		Matrix4	rotate;
		Vec4		tmp;
		Vec4		to_rotate;
		size_t		i = 0;

		rotate = rotate.rotation(_random_axis, _angle);
		while (i < _vert_indices.size())
		{
			to_rotate[0] = transformed_vertices[i * 3];
			to_rotate[1] = transformed_vertices[i * 3 + 1];
			to_rotate[2] = transformed_vertices[i * 3 + 2];
			tmp = rotate * to_rotate;
			transformed_vertices[i * 3] = tmp[0];
			transformed_vertices[i * 3 + 1] = tmp[1];
			transformed_vertices[i * 3 + 2] = tmp[2];
			i++;
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*transformed_vertices) * (_vert_indices.size() * 3), transformed_vertices, GL_STATIC_DRAW); 

		_changed = 0;
	}


	Matrix4		proj;
	proj = proj.perspective(angle_to_rad(45.0f), (float)(_width) / (float)(_height), 0.1f, 1000.0f);

	Matrix4		view;
	view = view.look_at(Vec4(0, 0, -5, 0), Vec4(0, 0, 0, 0), Vec4(0, 1, 0, 0));

	Matrix4		model;
	model = model.identity();

	Matrix4		rot;
	rot = model.rotation(_rotate_axis, angle_to_rad(_angle));

	_factor = check_moov(_factor);

	if (_angle >= 360)
		_angle = 0;
	else if (_spins)
		_angle += 1;

	GLuint	model_id = glGetUniformLocation(_programID, "model");
	GLuint	view_id = glGetUniformLocation(_programID, "view");
	GLuint	proj_id = glGetUniformLocation(_programID, "proj");
	GLuint	rot_id = glGetUniformLocation(_programID, "rot");
	GLuint	trans_id = glGetUniformLocation(_programID, "trans");
	GLuint	mod_id = glGetUniformLocation(_programID, "mod");
	GLuint	f_mod_id = glGetUniformLocation(_programID, "fmod");

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model._m[0]);
	glUniformMatrix4fv(view_id, 1, GL_FALSE, &view._m[0]);
	glUniformMatrix4fv(proj_id, 1, GL_FALSE, &proj._m[0]);
	glUniformMatrix4fv(rot_id, 1, GL_FALSE, &rot._m[0]);
	glUniform4f(trans_id, _factor[0], _factor[1], _factor[2], 0);
	glUniform1i(mod_id, _s_mod);
	glUniform1i(f_mod_id, _s_mod);
}

void	render::get_fps(float &last_time)
{
	float	current_time = glfwGetTime();
	_delta_time = current_time - last_time;
	_frames++;
	if (_delta_time >= 1.0)
	{
		std::stringstream	window_name;
		_ui_fps.str(std::string());
		_ui_fps << "fps: " << _frames << " (" << 1000.0/(float)_frames << ")";
		_frames = 0;
		last_time = glfwGetTime();
	}
}

void	render::printUI()
{
	printText(_ui_fps.str().c_str(), 5, 580, 20);
	std::stringstream	v_size;
	std::stringstream	model_name;
	model_name << "Name: " << _model_name << std::endl;
	v_size << "Polygons: " << std::to_string(_vertices.size() / 3).c_str();
	printText(v_size.str().c_str(), 5, 570, 10);
	printText(model_name.str().c_str(), 5, 560, 10);
}

void	render::toggle_fullscreen(std::string name)
{

	(void)name;
	if (!_is_fullscreen)
	{
		glfwGetWindowPos(_window, &_win_pos[0], &_win_pos[1]);
		glfwGetWindowSize(_window, &_win_dim[0], &_win_dim[1]);
		const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowMonitor(_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);
		glViewport(0, 0, mode->width, mode->height);
		_is_fullscreen = true;
	}
	else
	{
		glfwSetWindowMonitor(_window, NULL, _win_pos[0], _win_pos[1], _win_dim[0], _win_dim[1], 0);
		glViewport(0, 0, _width, _height);
		_is_fullscreen = false;
	}
}


//====================  CALLBACK  ====================

void	render::error_callback(int error, const char *description)
{
	(void)error;
	std::cout << "Error : " << description << std::endl;
}

void	render::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	void *data = glfwGetWindowUserPointer(window);
	render *w = static_cast<render *>(data);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_M)
		{
			if (!w->_wireframe)
			{
				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
				w->_wireframe = true;
			}
			else if (w->_wireframe)
			{
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
				w->_wireframe = false;
			}
		}
		if (key == GLFW_KEY_F3)
			w->_debug_mode = !w->_debug_mode;
		if (key == GLFW_KEY_F5)
			w->toggle_fullscreen("scop");
		if (key == GLFW_KEY_R)
			w->_factor = Vec4(0, 0, 0, 0);
		else if (key == GLFW_KEY_0)
			w->_spins = !w->_spins;
		else if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		else if (key == GLFW_KEY_T)
			w->switch_texture();
		else if (key == GLFW_KEY_L)
		{
			if (w->_s_mod == 0)
				w->_s_mod = 1;
			else
				w->_s_mod = 0;
		}
		w->_keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
		w->_keys[key] = false;
}

void	render::resize_callback(GLFWwindow *win, int width, int height)
{
	void	*data = glfwGetWindowUserPointer(win);
	render	*r = static_cast<render *>(data);
	(void)r;
	r->_width = width;
	r->_height = height;
	glViewport(0, 0, r->_width, r->_height);
}

void	render::handle_inputs()
{
	_moov_x = 0;
	_moov_y = 0;
	_moov_z = 0;
	_accelerate = 0;
	if (_keys[GLFW_KEY_W])
		_moov_z = -1;
	if (_keys[GLFW_KEY_S])
		_moov_z = 1;
	if (_keys[GLFW_KEY_A])
		_moov_x = -1;
	if (_keys[GLFW_KEY_D])
		_moov_x = 1;
	if (_keys[GLFW_KEY_SPACE])
		_moov_y = -1.5;
	if (_keys[GLFW_KEY_LEFT_SHIFT])
		_moov_y = 1.5;
	if (_keys[GLFW_KEY_LEFT_CONTROL])
		_accelerate = 5;
	if (_keys[GLFW_KEY_H] && _frames % 8 == 0)
	{
		_changed = 1;
		_random_axis = _rotate_axis + 1;
		if (_random_axis == 'z' + 1)
			_random_axis = 'y';
		_rotate_axis = _random_axis;
	}
	if (_keys[GLFW_KEY_RIGHT])
		_rotate_axis = 'x';
	else if (_keys[GLFW_KEY_UP])
		_rotate_axis = 'y';
	else if (_keys[GLFW_KEY_DOWN])
		_rotate_axis = 'z';
}


//====================  UTILS  ====================

float    *render::make_tex_mega_float(std::vector<float> uv, std::vector<unsigned int> uv_indices)
{
	float    *result = new float[uv_indices.size() * 2];
    size_t   i;

    i = 0;
    while (i < uv_indices.size())
    {
        result[2 * i] = uv[2 * (uv_indices[i] - 1)];
        result[2 * i + 1] = uv[2 * (uv_indices[i] - 1) + 1];
        i++;
    }
    return (result);
}


float    *render::make_mega_float(std::vector<float> vertices, std::vector<unsigned int> faces)
{
    float	*result = new float[faces.size() * 3];
    size_t	i;

    i = 0;
	while (i < faces.size())
    {
        result[3 * i] = vertices[3 * (faces[i] - 1)];
        result[3 * i + 1] = vertices[3 * (faces[i] - 1) + 1];
        result[3 * i + 2] = vertices[3 * (faces[i] - 1) + 2];
        i++;
    }
	to_center(result, faces.size());
    return (result);
}

void	render::to_center(float *result, size_t size)
{
	Matrix4		translate;
	Vec4		to_add;
	size_t		i;

	i = 0;
	while (i < size)
	{
		to_add[0] += result[3 * i];
		to_add[1] += result[3 * i + 1];
		to_add[2] += result[3 * i + 2];
		i++;
	}
	to_add[0] /= i;
	to_add[1] /= i;
	to_add[2] /= i;
	translate = translate.translate(to_add);
	i = 0;
	while (i < size)
	{
		result[3 * i] = result[3 * i] - translate[3];
		result[3 * i + 1] = result[3 * i + 1] - translate[7];
		result[3 * i + 2] = result[3 * i + 2] - translate[11];
		i++;
	}
}

Vec4	render::check_moov(Vec4 old)
{
	float	x = old[0];
	float	y = old[1];
	float	z = old[2];

	if (_moov_x != 0)
		x += _moov_x / 10 * _accelerate;
	if (_moov_y != 0)
		y += _moov_y / 10;
	if (_moov_z != 0)
		z += _moov_z / 10 * _accelerate;
	Vec4	factor(x, y, z, 1);
	return (factor);
}

void	render::switch_texture()
{
	if (_t_mode == 0)
	{
		glUniform3f(_color, 1.0f, 1.0f, 1.0f);
		_t_mode = 1;
	}
	else
	{
		glUniform3f(_color, 0.0f, 0.0f, 0.0f);
		_t_mode = 0;
	}
	
}

void	render::clear()
{
	std::cout << "CLEAR" << std::endl;
	glfwTerminate();
	exit(-1);
}

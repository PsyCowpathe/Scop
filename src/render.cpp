/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:26:34 by agirona           #+#    #+#             */
/*   Updated: 2023/08/04 19:47:43 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/render.hpp"

Texture *p_tex = NULL;

// CTOR inits a lot of things & loads shaders 
render::render(int aliasing, float openGL_min, float openGL_max, int width, int height, std::string name, std::vector<unsigned int> faces)
{
	_faces = faces;
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
	// glfwMaximizeWindow(_window);
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

	// not necessary
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	// I guess it's always a better practice to add those :	// but not necessary ?
	glDeleteBuffers(1, &_vertexArrayID);
	glDeleteBuffers(1, &_colorBuffer);
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_texBuffer);
	glfwDestroyWindow(_window);
	glfwTerminate();
}

float    *render::make_tex_mega_float(std::vector<float> uv, std::vector<unsigned int> uv_indices)
{
	float    *result = new float[uv_indices.size() * 2]; //dont forget delete[]
    size_t   i;

    i = 0;
	//std::cout << "face size " << faces.size() << std::endl;
	//std::cout << "vertices size " << vertices.size() << std::endl;
    while (i < uv_indices.size())
    {
		//std::cout << "face = " << faces[i] << std::endl;
		//std::cout << "vertices = " << vertices[i] << std::endl << std::endl;
		//std::cout << "crash = " << 3 * (faces[i] - 1) << std::endl;
		//std::cout << "wut =" << faces[i] - 1 << std::endl;
        result[2 * i] = uv[2 * (uv_indices[i] - 1)];
		//std::cout << "pas crash" << std::endl;
        result[2 * i + 1] = uv[2 * (uv_indices[i] - 1) + 1];
		std::cout << "result = " << result[2 * i] << " " << result[2 * i + 1] << std::endl;
        //std::cout << "face = " << faces[i] << " : x = " << result[3 * i] << " y = " << result[3 * i + 1] << " z = " << result[3 * i + 2] << std::endl;
        i++;
    }
    return (result);
}

float    *render::make_mega_float(std::vector<float> vertices, std::vector<unsigned int> faces)
{
    float    *result = new float[faces.size() * 3]; //dont forget delete[]
    size_t   i;

    i = 0;
	std::cout << "face size " << faces.size() << std::endl;
	std::cout << "vertices size " << vertices.size() << std::endl;
    while (i < faces.size())
    {
		//std::cout << "face = " << faces[i] << std::endl;
		//std::cout << "vertices = " << vertices[i] << std::endl << std::endl;
		//std::cout << "crash = " << 3 * (faces[i] - 1) << std::endl;
		//std::cout << "wut =" << faces[i] - 1 << std::endl;
        result[3 * i] = vertices[3 * (faces[i] - 1)];
		//std::cout << "pas crash" << std::endl;
        result[3 * i + 1] = vertices[3 * (faces[i] - 1) + 1];
        result[3 * i + 2] = vertices[3 * (faces[i] - 1) + 2];
        //std::cout << "face = " << faces[i] << " : x = " << result[3 * i] << " y = " << result[3 * i + 1] << " z = " << result[3 * i + 2] << std::endl;
        i++;
    }
    return (result);
}

void	render::get_fps(int &frames, float &last_time)
{
	float	current_time = glfwGetTime();
	_delta_time = current_time - last_time;
	frames++;
	if (_delta_time >= 1.0)
	{
		std::stringstream ss;
		ss << "Scop [fps: " << frames << " | time: " << 1000.0/(float)frames << "]";
		glfwSetWindowTitle(_window, ss.str().c_str());
		frames = 0;
		last_time = glfwGetTime();
	}
}

Vec4	render::check_moov(Vec4 old)
{
	float	x = old[0];
	float	y = old[1];
	float	z = old[2];

	if (_moov_x != 0)
		x += _moov_x / 60;
	if (_moov_y != 0)
		y += _moov_y / 60;
	if (_moov_z != 0)
		z += _moov_z / 60;
	Vec4	factor(x, y, z, 1);
	return (factor);
}

// This is our VAO
void	render::create_vertex_array()
{
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);
}

void	render::update()
{
	Matrix4		proj;
	proj = proj.perspective(angle_to_rad(45.0f), (float)(_width) / (float)(_height), 0.1f, 100.0f);

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
		_angle += .1;

	GLuint	model_id = glGetUniformLocation(_programID, "model");
	GLuint	view_id = glGetUniformLocation(_programID, "view");
	GLuint	proj_id = glGetUniformLocation(_programID, "proj");
	GLuint	rot_id = glGetUniformLocation(_programID, "rot");
	GLuint	trans_id = glGetUniformLocation(_programID, "trans");
	// might need to move this to render since it's shader related
	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model._m[0]);
	glUniformMatrix4fv(view_id, 1, GL_FALSE, &view._m[0]);
	glUniformMatrix4fv(proj_id, 1, GL_FALSE, &proj._m[0]);
	glUniformMatrix4fv(rot_id, 1, GL_FALSE, &rot._m[0]);
	glUniform4f(trans_id, _factor[0], _factor[1], _factor[2], 0);
}

void	render::loop(std::vector<float> vertices, std::vector<unsigned int> faces, std::vector<float> uv, std::vector<unsigned int> uv_indices)
{
	std::vector<float>		tmp;
	std::vector<float>		vertex(4);
	// TODO: disable fps before correc since using glfw function
	float					*transformed_vertices = make_mega_float(vertices, faces);
	float					*transformed_uv = make_tex_mega_float(uv, uv_indices);

	
	// ************
	// * VERTICES *
	// ************

	// // CREATING VERTEX BUFFER
	//std::cout << vertices.size() << std::endl;
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	// static draw flag : "The data store contents will be modified once and used many times as the source for GL drawing commands. "
	glBufferData(GL_ARRAY_BUFFER, sizeof(*transformed_vertices) * (faces.size() * 3), transformed_vertices, GL_STATIC_DRAW); 	

	glVertexAttribPointer
		(
		 0,				// attribute 0. No particular reason for 0, but must match the layout in the shader.
		 3,				// size (here we have 3 values per vertex)
		 GL_FLOAT,		// type
		 GL_FALSE,		// normalized?
		 0,				// stride (y-a-t il un ecart entre les donnes de chaque vertice dans l'array ?)
		 (void*)0		// array buffer offset (at beginning of array)
		);
	// glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds previously bound buffer
	
	// Colored BG : Used in change_color() & switch_texture()
	this->_color = glGetUniformLocation(_programID, "u_color");
	glUniform3f(this->_color, 1.0f, 1.0f, 1.0f);

	// ************
	// * TEXTURES *
	// ************

	p_tex = new Texture(GL_TEXTURE_2D, "objects/bricks.bmp", this);
	p_tex->load_tex();

	GLuint gSamplerLocation = glGetUniformLocation(_programID, "gSampler");
	if (gSamplerLocation == 0)
	{
		std::cout << "Error getting uniform location of 'gSampler'" << std::endl;
     	clear();
    }
	glUniform1i(gSamplerLocation, 0);


	// GENERATE & FILL TEXCOORDINATES BUFFER
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &_texBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _texBuffer);
	std::cout << " size = " << sizeof(*transformed_uv) * (uv.size() * 2) << std::endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(*transformed_uv) * (uv.size() * 2), transformed_uv, GL_STATIC_DRAW); //SEGFAULT WITH FSANITIZE A PATCH
	
	// send texBuffer to shader pipeline, at layout = 1
	glVertexAttribPointer
		(
		 1,				// attribute 0. No particular reason for 0, but must match the layout in the shader.
		 2,				// size (here we have 2 values per vertex)
		 GL_FLOAT,		// type
		 GL_FALSE,		// normalized?
		 0,				// stride (y-a-t il un ecart entre les donnes de chaque vertice dans l'array ?)
		 (void*)0		// array buffer offset (at beginning of array)
		);

	// ***************
	// * RENDER LOOP *
	// ***************
	int frames = 0;
	float	last_time = glfwGetTime();
	while (!glfwWindowShouldClose(_window))
	{
		handle_inputs();
		update();
		draw();
		get_fps(frames, last_time);
	}
}

void	render::draw()
{
	glUseProgram(_programID);

	glClearColor(.2, .2, .2, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// "Wireframe" render mode :)
	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glDrawArrays(GL_TRIANGLES, 0, _faces.size()); // Starting from vertex 0;
	glfwSwapBuffers(_window);
	glfwSetWindowUserPointer(_window, this);
	glfwPollEvents();
	glFinish();
	// key_print();
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

int		render::create_window(std::string name)
{
	_window = glfwCreateWindow(_width, _height, name.c_str(), NULL, NULL);
	if (!_window)
	{
		std::cout << "GLFW window creation failed :(" << std::endl;
		return (-1);
	}
	return (1);
}

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
	std::cout << "refresh : " << mode->refreshRate << std::endl;
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	// glfwWindowHint(GLFW_DECORATED, 0);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

void	render::clear()
{
	std::cout << "CLEAR" << std::endl;
	glfwTerminate();
	exit(-1);
}

void	render::error_callback(int error, const char *description)
{
	(void)error;
	std::cout << "Error : " << description << std::endl;
}

void	render::handle_inputs()
{
	_moov_x = 0;
	_moov_y = 0;
	_moov_z = 0;
	if (_keys[GLFW_KEY_W])
		_moov_z = -1;
	if (_keys[GLFW_KEY_S])
		_moov_z = 1;
	if (_keys[GLFW_KEY_A])
		_moov_x = 1;
	if (_keys[GLFW_KEY_D])
		_moov_x = -1;
	if (_keys[GLFW_KEY_SPACE])
		_moov_y = 1;
	if (_keys[GLFW_KEY_LEFT_SHIFT])
		_moov_y = -1;
	if (_keys[GLFW_KEY_RIGHT])
		_rotate_axis = 'x';
	else if (_keys[GLFW_KEY_UP])
		_rotate_axis = 'y';
	else if (_keys[GLFW_KEY_DOWN])
		_rotate_axis = 'z';

	// ADD CODE HERE !
}

// needs to be re-done, or dropped
void	render::change_color(int key)
{
	if (key == GLFW_KEY_R)
		glUniform3f(_color, 1.0f, 0.0f, 0.0f);
	else if (key == GLFW_KEY_G)
		glUniform3f(_color, 0.0f, 1.0f, 0.0f);
	else if (key == GLFW_KEY_B)
		glUniform3f(_color, 0.0f, 0.0f, 1.0f);
	else if (key == GLFW_KEY_C)
		glUniform3f(_color, 1.0f, 1.0f, 1.0f);
}

// needs to be re-done
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
		else if (key == GLFW_KEY_0)
			w->_spins = !w->_spins;
		else if ((key == GLFW_KEY_R || key == GLFW_KEY_G || key == GLFW_KEY_B || key == GLFW_KEY_C ))
			w->change_color(key);
		else if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		else if (key == GLFW_KEY_T)
			w->switch_texture();
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

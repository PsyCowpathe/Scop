/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:26:34 by agirona           #+#    #+#             */
/*   Updated: 2023/08/01 17:39:43 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/render.hpp"

render::render(int aliasing, float openGL_min, float openGL_max, int width, int height, std::string name)
{
	std::cout << "creation" << std::endl;
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
	if (glew_init() == -1)
		clear();
}

render::~render()
{
	std::cout << "destruction" << std::endl;
	glfwTerminate();
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
        result[3 * i] = vertices[3 * (faces[i] - 1)];
        result[3 * i + 1] = vertices[3 * (faces[i] - 1) + 1];
        result[3 * i + 2] = vertices[3 * (faces[i] - 1) + 2];
        std::cout << "face = " << faces[i] << " : x = " << result[3 * i] << " y = " << result[3 * i + 1] << " z = " << result[3 * i + 2] << std::endl;
        i++;
    }
    std::cout << "blaaaaaaaaaaaaaaaaaa" << std::endl;
    return (result);
}

/*float	*render::make_mega_float(std::vector<vec3> vertices, std::vector<unsigned int> faces)
{
	float	*result = new float[faces.size()]; //dont forget delete[]
	size_t		i;

	i = 0;
	
	while (i < faces.size())
	{
		tmp = vertices[faces[i] - 1];
		std::cout << "vert = " << faces[i] << " : ";
		result[3 * i] = tmp._v[0];
		result[3 * i + 1] = tmp._v[1];
		result[3 * i + 2] = tmp._v[2];
		std::cout << "x = " << result[3 * i] << " y = " << result[3 * i + 1] << " z = " << result[3 * i + 2] << std::endl;
		i++;
	}
		// tmp = vertices[faces[i] - 1];
		std::cout << "tessst" << std::endl;
		std::cout << vertices[faces[i] - 1]._v[0];
		std::cout << "==============" << std::endl;
		result[3 * i] = vertices[3 * (faces[i] - 1)];
		result[3 * i + 1] = vertices[3 * (faces[i] - 1) + 1];
		result[3 * i + 2] = vertices[3 * (faces[i] - 1) + 2];
		std::cout << "face = " << faces[i] << " : x = " << result[3 * i] << " y = " << result[3 * i + 1] << " z = " << result[3 * i + 2] << std::endl;

		std::cout << std::endl << "mega float res = " << std::endl;
		std::cout << result[3 * i] << ", ";
		std::cout << result[3 * i + 1] << ", ";
		std::cout << result[3 * i + 2] << std::endl;
		i++;
	}
	i = 0;
	std::cout << "[";
	while(i < faces.size() * 3)
	{
		std::cout << std::fixed << std::setprecision(8) << result[i++];
		if (i % 3 == 0)
			std::cout << "]" << std::endl << "[";
		else
			std::cout << ", ";
	}
	std::cout << "blaaaaaaaaaaaaaaaaaa" << std::endl;
	return (result);
}*/

/*float	*render::make_perspective(float *mega_float, int size)
{
	int		i;
	float	x;
	float	y;
	float	z;
	float	ar;

	ar = _width / _height;
	i = 0;
	while (i < size)
	{
		x = mega_float[3 * i];
		y = mega_float[3 * i + 1];
		z = mega_float[3 * i + 2];
		mega_float[3 * i] = x / (ar * z * tanf((90 / 2) * (M_PI / 180)));
		mega_float[3 * i + 1] = x / (z * tanf((90 / 2) * (M_PI / 180)));
		i++;
	}
	return (mega_float);
}*/

static void	getFps(int &frames, float &last_time)
{
	float	current_time = glfwGetTime();
	frames++;
	if (current_time - last_time >= 1.0)
	{
		std::cout << "fps: " << frames << " frame time: " << 1000.0/float(frames) << std::endl;
		frames = 0;
		last_time = glfwGetTime();
	}
}

void	render::draw_triangle(std::vector<float> vertices, std::vector<unsigned int> faces)
{
	(void)faces;
	(void)vertices;
	// float					angle = 0;
	// size_t					i;
	std::vector<float>		tmp;
	std::vector<float>		vertex(4);
	// float					*mega_float;
	int						frames = 0;
	// TODO: disable fps before correc since using glfw function
	float					last_time = glfwGetTime();

	// GLfloat 			new_vertex[faces.size() * 3];

	//_original_vertex = vertex_buffer;
	//_current_vertex = static_cast<float *>(_original_vertex);
	create_vertex_array();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	GLuint		programID = LoadShaders("shader/vertex_shader.vert", "shader/frag_shader.frag"); //tmp
	Matrix4		proj;
	proj = proj.perspective(angle_to_rad(45.0f), 4.0f, 0.1f, 1000.f);

	Matrix4		view;
	view = view.look_at(Vec4(4, 3, 3, 0), Vec4(0, 0, 0, 0), Vec4(0, 1, 0, 0));

	Matrix4		model;
	model = model.identity();

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
	// mega_float = make_mega_float(vertices, faces);
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint	model_id = glGetUniformLocation(programID, "model");
	GLuint	view_id = glGetUniformLocation(programID, "view");
	GLuint	proj_id = glGetUniformLocation(programID, "proj");
	while (!glfwWindowShouldClose(_window))
	{
		getFps(frames, last_time);
		glClearColor(0, 255, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		glUniformMatrix4fv(model_id, 1, GL_FALSE, &model._m[0]);
		glUniformMatrix4fv(view_id, 1, GL_FALSE, &view._m[0]);
		glUniformMatrix4fv(proj_id, 1, GL_FALSE, &proj._m[0]);
		
		// glBufferData(GL_ARRAY_BUFFER, sizeof(*mega_float) * (faces.size() * 3), mega_float, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glVertexAttribPointer
			(
			 0,
			 3,
			 GL_FLOAT,
			 GL_FALSE,
			 0,
			 (void*)0
			);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		// glDisableVertexAttribArray(1);
		glfwSwapBuffers(_window);
		glfwSetWindowUserPointer(_window, this);
		glfwPollEvents();
	}
	// delete[] mega_float;
}

void	render::create_vertex_array()
{
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);
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
	glewExperimental = true;
}

void	render::set_callback()
{
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(_window, key_callback);
}

int		render::create_window(std::string name)
{
	_window = glfwCreateWindow(_width, _height, name.c_str(), NULL, NULL);
	if (!_window)
	{
		std::cout << "GLFW Init failed :(" << std::endl;
		return (-1);
	}
	return (1);
}

void	render::set_hint(int aliasing, float openGL_min, float openGL_max)
{
	glfwWindowHint(GLFW_SAMPLES, aliasing);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGL_min);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGL_max);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

void	render::clear() //comment on sait dans le main qu'il y a eu un clear et stop le prgm ?
{
	glfwTerminate();
}

void	render::error_callback(int error, const char *description)
{
	(void)error;
	std::cout << "Error : " << description << std::endl;
}

void	render::change_rotate_axis(int key)
{
	if (key == GLFW_KEY_RIGHT)
		_rotate_axis = 'x';
	else if (key == GLFW_KEY_UP)
		_rotate_axis = 'y';
	else if (key == GLFW_KEY_DOWN)
		_rotate_axis = 'z';
}

void	render::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	void *data = glfwGetWindowUserPointer(window);  
	render *w = static_cast<render *>(data);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else
		w->change_rotate_axis(key);

}

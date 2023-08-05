/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:26:34 by agirona           #+#    #+#             */
/*   Updated: 2023/08/03 16:29:53 by agirona          ###   ########.fr       */
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

	// not necessary
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	// I guess it's always a better practice to add those :	// but not necessary ?
	glDeleteBuffers(1, &_vertexArrayID);
	glDeleteBuffers(1, &_colorBuffer);
	glDeleteBuffers(1, &_vertexBuffer);
	glfwDestroyWindow(_window);
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
    return (result);
}

static void	get_fps(int &frames, float &last_time)
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

	// Define viewport dimensions ??
	// glViewport(0, 0, _width, _height);

	// Enable/init depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Add culling (1st line culls backfaces by default, so 2nd line is optionnal ?)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	GLuint		programID = LoadShaders("shader/vertex_shader.vert", "shader/frag_shader.frag"); //tmp
	// Matrix4		proj;
	// proj = proj.perspective(angle_to_rad(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Matrix4		view;
	// float		pos = 0.0f;
	// view = view.look_at(Vec4(pos, 3, -3, 0), Vec4(0, 0, 0, 0), Vec4(0, -1, 0, 0));

	// Matrix4		model;
	// model = model.identity();


	// CREATING VERTICES
	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

	static const GLfloat color_buffer[] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};
	
	glGenBuffers(1, &_colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer), color_buffer, GL_STATIC_DRAW);


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);

	// send _colorBuffer to shader pipeline, at layout = 1
	glVertexAttribPointer
		(
		 1,				// attribute 0. No particular reason for 0, but must match the layout in the shader.
		 3,				// size (here we have 3 values per vertex)
		 GL_FLOAT,		// type
		 GL_FALSE,		// normalized?
		 0,				// stride (y-a-t il un ecart entre les donnes de chaque vertice dans l'array ?)
		 (void*)0		// array buffer offset (at beginning of array)
		);


	// VERTEX BUFFER
	glGenBuffers(1, &_vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); 
	// static draw flag : "The data store contents will be modified once and used many times 
	//as the source for GL drawing commands. "

	GLuint	model_id = glGetUniformLocation(programID, "model");
	GLuint	view_id = glGetUniformLocation(programID, "view");
	GLuint	proj_id = glGetUniformLocation(programID, "proj");
	float		pos = 0.0f;


	// Trying to set some uniforms (add uniforms locations to render class ?)
	GLuint my_uniform = glGetUniformLocation(programID, "u_test");
	glUniform1f(my_uniform, 3.0f);

	// Used in change_color() & switch_texture()
	this->_color = glGetUniformLocation(programID, "u_color");
	glUniform3f(this->_color, 1.0f, 1.0f, 1.0f);

	// Trying to load bmp file !!
	GLuint tex;
	load_bmp("objects/sample.bmp", tex);

	// ***************
	// * RENDER LOOP *
	// ***************

	while (!glfwWindowShouldClose(_window))
	{
		Matrix4		proj;
		proj = proj.perspective(angle_to_rad(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

		Matrix4		view;
		view = view.look_at(Vec4(pos, 3, -3, 0), Vec4(0, 0, 0, 0), Vec4(0, -1, 0, 0));

		Matrix4		model;
		model = model.identity();
		get_fps(frames, last_time);

		// BACKGROUND clear & redraw
		// glClearColor(0, 255, 0, 1); // Basic colored bg

		// Spice up BG :)
		static GLclampf c = 0.0f;
		//Why not a colred bg ?
		glClearColor(c,c,c,1);
		c += 1.0f/256.0f;
		if (c >= 1.0f)
			c = 0.0f;


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Loop on every face's vertices to transform/rotate/etc. them

		// while (i < faces.size())
		// {
			/*std::vector<float>	test(4, 0);
			test[0] = 0 + (angle / 1000);
			test[1] = (0);
			test[2] = (0);
			test[3] = (0);*/

		glUniformMatrix4fv(model_id, 1, GL_FALSE, &model._m[0]);
		glUniformMatrix4fv(view_id, 1, GL_FALSE, &view._m[0]);
		glUniformMatrix4fv(proj_id, 1, GL_FALSE, &proj._m[0]);
		
		// glBufferData(GL_ARRAY_BUFFER, sizeof(*mega_float) * (faces.size() * 3), mega_float, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		// glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glVertexAttribPointer
			(
			 0,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
			 3,			// size
			 GL_FLOAT,	// type
			 GL_FALSE,	// normalized?
			 0,			// stride
			 (void*)0	// array buffer offset
			);


		// "Wireframe" render mode :)
    	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


    	// Gives the current buffer binded to GL_ARRAY_BUFFER as vertices data to your shader (the shader will draw the triangle)
		glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle per face

		// glDisableVertexAttribArray(0); // not necessary
		
		glUseProgram(programID);
		
		glfwSwapBuffers(_window);
		glfwSetWindowUserPointer(_window, this);
		glfwPollEvents();
		pos += .1f;
	}
	// END OF RENDER LOOP

	// delete[] mega_float;
}

// This is our VAO ?
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
	std::cout << "CLEAR" << std::endl;
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

	std::cout << "KEY CODE = " << key << std::endl;
	
	if ((key == GLFW_KEY_R || key == GLFW_KEY_G || key == GLFW_KEY_B || key == GLFW_KEY_C )
				&& action == GLFW_PRESS)
		w->change_color(key);
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else if (key == GLFW_KEY_T && action == GLFW_PRESS)
		w->switch_texture();
	else
		w->change_rotate_axis(key);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:26:34 by agirona           #+#    #+#             */
/*   Updated: 2023/08/02 17:20:17 by agirona          ###   ########.fr       */
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

static void	getFps(int &frames, float &last_time)
{
	float	current_time = glfwGetTime();
	frames++;
	if (current_time - last_time >= 1.0)
	{
		std::cout << "fps: " << frames << " frame time: " << 1000.0/float(frames) << std::endl;
		//frames = 0;
		last_time = glfwGetTime();
	}
}

void	render::draw_triangle(std::vector<float> vertices, std::vector<unsigned int> faces)
{
	float					angle = 0;
	size_t					i;
	std::vector<float>		tmp(4);
	std::vector<float>		vertex(4);
	float					*mega_float;
	int						frames = 0;
	// TODO: disable fps before correc since using glfw function
	float					last_time = glfwGetTime();

	std::vector<float>		rotation;
	std::vector<float>		scale;
	std::vector<float>		translate;
	std::vector<float>		projection;
	std::vector<float>		camera;
	std::vector<float>	world;
	std::vector<float>	wvp;

	GLfloat 			new_vertex[faces.size() * 4];

	//_original_vertex = vertex_buffer;
	//_current_vertex = static_cast<float *>(_original_vertex);
	create_vertex_array();
	//glGenBuffers(1, &_vertexBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(*vertex_buffer) * 27, vertex_buffer, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	GLuint		programID = LoadShaders("shader/vertex_shader.vert", "shader/frag_shader.frag"); //tmp


	static const GLfloat color_buffer[] =
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.5f,
		0.0f, 0.2f, 0.3f,
		0.2f, 0.3f, 0.0f,
		0.8f, 0.6f, 0.4f,
		0.9f, 0.1f, 0.5f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.5f,
		0.0f, 0.2f, 0.3f,
		0.2f, 0.3f, 0.0f,
		0.8f, 0.6f, 0.4f,
		0.9f, 0.1f, 0.5f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.5f,
		0.0f, 0.2f, 0.3f,
		0.2f, 0.3f, 0.0f,
		0.8f, 0.6f, 0.4f,
		0.9f, 0.1f, 0.5f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.5f,
		0.0f, 0.2f, 0.3f,
		0.2f, 0.3f, 0.0f,
		0.8f, 0.6f, 0.4f,
		0.9f, 0.1f, 0.5f,
	};


	GLuint	colorbuffer;

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer), color_buffer, GL_STATIC_DRAW);


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer
		(
		 1,
		 3,
		 GL_FLOAT,
		 GL_FALSE,
		 0,
		 (void*)0
		);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

	mega_float = make_mega_float(vertices, faces);
	
	while (!glfwWindowShouldClose(_window))
	{
		getFps(frames, last_time);
		glClearColor(0, 255, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		i = 0;

		while (i < faces.size())
		{
			vertex[0] = mega_float[3 * i];
			vertex[1] = mega_float[3 * i + 1];
			vertex[2] = mega_float[3 * i + 2];
			vertex[3] = 1;

			std::vector<float>	eye(4, 0);
			std::vector<float>	center(4, 0);
			std::vector<float>	up(4, 0);

			eye[0] = 10;
			eye[1] = 10;
			eye[2] = 0;

			center[0] = 0;
			center[1] = 0;
			center[2] = 0;

			up[0] = 0;
			up[1] = 1;
			up[2] = 0;

			std::vector<float>	test(4, 0);
			test[0] = 0;// + (angle );
			test[1] = 0 + (angle / 10);
			test[2] = 0 ;//+ (angle / 10);
			test[3] = 0;

			std::vector<float> CameraPos(3, 0);
			CameraPos[0] = 0.0f;
			CameraPos[1] = 1.0f;
			CameraPos[2] = 0.0f; //si pas a 0 = casse

			std::vector<float> U(3, 0);
			U[0] = 1.0f;
			U[1] = 0.0f;
			U[2] = 0.0f;

			std::vector<float> V(3, 0);
			V[0] = 0.0f;
			V[1] = 1.0f;
			V[2] = 0.0f;

			std::vector<float> N(3, 0);
			N[0] = 0.0f;
			N[1] = 0.0f;
			N[2] = 1.0f;

			rotation = matrice.create_rotate_matrice(_rotate_axis, angle);
			//scale = create_scale_matrice();
			translate = matrice.create_translate_matrice(test);
			projection = matrice.create_projection_matrice(_width, _height);
			camera = matrice.create_view_matrice(eye, center, up);


			//BON ORDRE
			wvp = matrice.multiply_mm(translate, rotation);
			wvp = matrice.multiply_mm(camera, wvp);
			wvp = matrice.multiply_mm(projection, wvp);
			tmp = matrice.multiply_mv(wvp, vertex);
			

			/*std::cout << "AVANT"<< std::endl;
			std::cout << tmp[0] << ", ";
			std::cout << tmp[1] << ", ";
			std::cout << tmp[2] << ", ";
			std::cout << tmp[3] << std::endl << std::endl;

			std::cout << "APRES"<< std::endl;
			std::cout << tmp[0] << ", ";
			std::cout << tmp[1] << ", ";
			std::cout << tmp[2] << ", ";
			std::cout << tmp[3] << std::endl << std::endl;*/



			new_vertex[3 * i] = tmp[0];
			new_vertex[3 * i + 1] = tmp[1];
			new_vertex[3 * i + 2] = tmp[2];
			new_vertex[3 * i + 3] = tmp[3];


			i++;
		}

		if (angle == 360)
			angle = 0;
		else
			angle += 0.01;
		glBufferData(GL_ARRAY_BUFFER, sizeof(*new_vertex) * (faces.size() * 4), new_vertex, GL_STATIC_DRAW);

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


		glDrawArrays(GL_TRIANGLES, 0, (faces.size() * 4)); //- (4 * 30));
		glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);
		glUseProgram(programID);
		glfwSwapBuffers(_window);
		glfwSetWindowUserPointer(_window, this);
		glfwPollEvents();
	}
	delete[] mega_float;
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

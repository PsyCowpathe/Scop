// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

#include <GLFW/glfw3.h>
// Include GLM
// #include "../inc/glm.hpp>
// using namespace glm;

#include "../shader/shader.hpp"

void    initGlfw()
{
    if (!glfwInit())
    {
        // Initialization failed
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int	initGlew()
{
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return (-1);
    }
	return(0);
}

int    vao()
{  
    GLuint VertexArrayID;
    glEnableVertexAttribArray(0);
    glGenVertexArrays(1, &VertexArrayID);

	// Specifying that this is the Vertex array we're gonna use
    glBindVertexArray(VertexArrayID);
    return (1);
}

GLuint	triangle(GLuint* vertexbuffer)
{
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };

    std::cout << g_vertex_buffer_data[0] << " " << g_vertex_buffer_data[4] << " " << g_vertex_buffer_data[8] << " " << g_vertex_buffer_data[12] << std::endl;
    std::cout << g_vertex_buffer_data[1] << " " << g_vertex_buffer_data[5] << " " << g_vertex_buffer_data[9] << " " << g_vertex_buffer_data[13] << std::endl;
    std::cout << g_vertex_buffer_data[2] << " " << g_vertex_buffer_data[6] << " " << g_vertex_buffer_data[10] << " " << g_vertex_buffer_data[14] << std::endl;
    std::cout << g_vertex_buffer_data[3] << " " << g_vertex_buffer_data[7] << " " << g_vertex_buffer_data[11] << " " << g_vertex_buffer_data[15] << std::endl;

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    return(*vertexbuffer);
}

void    drawTriangle(GLuint* vertexbuffer)
{
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    // glDrawArrays(GL_LINES, 0, 1);
	// glDrawArrays(GL_LINES, 2, 3);
	// glDrawArrays(GL_LINES, 0, 3);
    glDisableVertexAttribArray(0);
}

GLFWwindow*    openWindow()
{
    //                                      width, height, name, fullscreen, ?
    GLFWwindow* window = glfwCreateWindow(640, 480, "TRUITE", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        glfwTerminate();
        return (window);
    }

    glfwMakeContextCurrent(window); 
    return (window);
}

void transformTriangle(GLuint* vertexbuffer)
{
        // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };

    std::cout << g_vertex_buffer_data[0] << " " << g_vertex_buffer_data[4] << " " << g_vertex_buffer_data[8] << " " << g_vertex_buffer_data[12] << std::endl;
    std::cout << g_vertex_buffer_data[1] << " " << g_vertex_buffer_data[5] << " " << g_vertex_buffer_data[9] << " " << g_vertex_buffer_data[13] << std::endl;
    std::cout << g_vertex_buffer_data[2] << " " << g_vertex_buffer_data[6] << " " << g_vertex_buffer_data[10] << " " << g_vertex_buffer_data[14] << std::endl;
    std::cout << g_vertex_buffer_data[3] << " " << g_vertex_buffer_data[7] << " " << g_vertex_buffer_data[11] << " " << g_vertex_buffer_data[15] << std::endl;

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

int main()
{
	// Init 3rd party libs (window, driver, extensions support)
    initGlfw();
    GLFWwindow* window = openWindow();

    initGlew();

	// Init VAO/VBO with our vertex data
	vao();

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    triangle(&vertexbuffer);

    // Create and compile our GLSL program from the shader
    GLuint programID = loadShaders("./shader/vert.vert", "./shader/frag.frag");



    // MAIN RENDER LOOP !
    while (!glfwWindowShouldClose(window))
    {
		// Spice up BG :)
		static GLclampf c = 0.0f;
		//Why not a colred bg ?
		glClearColor(c,c,c,1);
		c += 1.0f/256.0f;
		if (c >= 1.0f)
			c = 0.0f;
        // clear the screen first (applying a color if glClearColor has been called/set before !)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TEST : tring to rotate triangle placed in vertexbuffer here
        //transformTriangle(&vertexbuffer);

        drawTriangle(&vertexbuffer);


        // use our shader to ACTUALLY draw the triangle we defined ! But do we have to do it in each loop ?.. Not sure.
        glUseProgram(programID);
        
        // Keep watching for inputs until a closing window input occurs :
        glfwPollEvents();

        // Swap buffers to display the result of all the above code in the loop
        glfwSwapBuffers(window);
    }

    //glfwDestroyWindow(window);
    //glfwTerminate();
    std::cout << "HARICOT" << std::endl;
    return (1);
}
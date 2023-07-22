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

int    vao()
{
    // init Glew :)
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    
    GLuint VertexArrayID;
    glEnableVertexAttribArray(0);
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    return (1);
}

GLuint triangle(GLuint* vertexbuffer)
{
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };


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
    glDisableVertexAttribArray(0);
}

int    openWindow()
{
    //                                      width, height, name, fullscreen, ?
    GLFWwindow* window = glfwCreateWindow(640, 480, "TRUITE", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        glfwTerminate();
        return (-1);
    }

    glfwMakeContextCurrent(window);
    vao();
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    triangle(&vertexbuffer);

    // Create and compile our GLSL program from the shader
    GLuint programID = loadShaders("./shader/vert.vert", "./shader/frag.frag");

    // MAIN LOOP !
    while (!glfwWindowShouldClose(window))
    {
        // clear the screen first
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawTriangle(&vertexbuffer);


         // Swap buffers
        glfwSwapBuffers(window);

        // use our shader !
        glUseProgram(programID);
        
        // Keep running
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return (1);
}


int main()
{
    initGlfw();
    openWindow();


    return (1);
}
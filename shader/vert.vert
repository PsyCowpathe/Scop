#version 330 core

// layout (location = index where vertex begin in the Vertex Attrib Pointer ?)
layout(location = 0) in vec3 vertexPosition_modelspace;

void    main()
{
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
}
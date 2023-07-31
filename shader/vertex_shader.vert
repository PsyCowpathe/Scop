#version 330 core
layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec3 vertex_color;

out vec3 color;
void main()
{
	gl_Position = vertexPosition_modelspace;
	color = vertex_color;
}

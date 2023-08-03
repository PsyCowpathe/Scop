#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 in_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 rot;
uniform vec4 trans;

out vec3 color;
void main()
{
	gl_Position = vec4(vertexPosition_modelspace, 1.0f);
	gl_Position = proj * view *  model * (trans + (rot * vec4(vertexPosition_modelspace, 1.0f)));

	color = in_color;
}

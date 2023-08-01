#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 in_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 color;
void main()
{
	//gl_Position.xyz = vertexPosition_modelspace;
	//gl_Position.w = 1.0;
	gl_Position = proj * view * model * vec4(vertexPosition_modelspace, 1.0);
	color = in_color;
}

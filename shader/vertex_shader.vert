#version 330 core
// layout(location = 0) in vec3 position;
layout(location = 0) in vec3 vertexPosition_modelspace;
// layout(location = 1) in vec3 in_color;
layout(location = 1) in vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 rot;
uniform vec4 trans;

uniform float u_test;
uniform vec3 u_color;


// out vec3 color;
out vec2 TexCoord0;

out vec4 color;
void main()
{
	gl_Position = proj * view *  model * (trans + (/*rot **/ vec4(vertexPosition_modelspace, 1.0f)));

	TexCoord0 = TexCoord;
	// color = vec4(in_color, 1.0f);
	// color = vec4(vertexPosition_modelspace, 1.0);
}

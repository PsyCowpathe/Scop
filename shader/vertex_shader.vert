#version 330 core
layout(location = 0) in vec3 position;
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 in_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform float u_test;

out vec3 color;


// attribute vec3 position;
in vec3 normal;
uniform mat4 normalMat;
// uniform mat4 projection, modelview, normalMat;

out vec3 normalInterp;
out vec3 vertPos;

void main()
{
	gl_Position = vec4(vertexPosition_modelspace, 1.0f);
	gl_Position = proj * view *  model * vec4(vertexPosition_modelspace, 1.0f);

	// from shaded mtl thingy
	// vec4 vertPos4 = model * vec4(position, 1.0);
  	// vertPos = vec3(vertPos4) / vertPos4.w;
  	// normalInterp = vec3(normalMat * vec4(normal, 0.0));
  	// gl_Position = proj * vertPos4;

	color = in_color;
}

#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 rot;
uniform vec4 trans;

uniform int mod;

out vec2 TexCoord0;
out vec4 color;

float random (vec2 st) {
	return fract(sin(dot(st.xy,
		vec2(12.9898,78.233)))*
		43758.5453123);
}

void main()
{
	gl_Position = proj * view *  model * (trans + (rot * vec4(vertexPosition_modelspace, 1.0f)));
	if (mod == 	1)
		TexCoord0 = TexCoord;
	else
		color = vec4(random(vec2(vertexPosition_modelspace.x, vertexPosition_modelspace.y)), random(vec2(vertexPosition_modelspace.x * 2, vertexPosition_modelspace.y * 2)), random(vec2(vertexPosition_modelspace.x *3, vertexPosition_modelspace.y *3)), 1.0);
}

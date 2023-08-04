#version 330 core

in  vec3 color;
out vec3 colore;

uniform float u_test;
uniform vec3 u_color;


void main()
{
  // colore = color * u_test ;
  colore = vec3((color.r * u_color.r),
                  (color.g * u_color.g),
                  (color.b * u_color.b)
  );
}

#version 330 core

in  vec3 color;
out vec3 colore;
out vec4 FragColor;

in  vec2 TexCoord0;
uniform sampler2D gSampler;

uniform float u_test;
uniform vec3 u_color;


void main()
{

  // colore = vec3((color.r * u_color.r),
  //                 (color.g * u_color.g),
  //                 (color.b * u_color.b)
  // );

  // TEXTURE work in progress
  FragColor = texture2D(gSampler, TexCoord0);
  // FragColor.r = 0.5f;

}

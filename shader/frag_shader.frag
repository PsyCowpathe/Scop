#version 330 core

uniform sampler2D		gSampler;
in  vec4				color;
in  vec2				TexCoord0;
out vec4				FragColor;


void main()
{
  FragColor = texture2D(gSampler, TexCoord0);
  //FragColor.r = 0.5f;
}

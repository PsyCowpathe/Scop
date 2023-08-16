#version 330 core

uniform sampler2D		gSampler;
in  vec4				color;
in  vec2				TexCoord0;
out vec4				FragColor;

uniform int fmod;

void main()
{
  if (fmod == 1)
    FragColor = texture2D(gSampler, TexCoord0);
  else
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}

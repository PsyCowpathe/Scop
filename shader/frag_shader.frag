#version 330 core

in  vec3 color;
out vec3 colore;


// precision mediump float;
// in vec3 normalInterp;  // Surface normal
// in vec3 vertPos;       // Vertex position
// uniform int mode;   // Rendering mode
// uniform float Ka;   // Ambient reflection coefficient
// uniform float Kd;   // Diffuse reflection coefficient
// uniform float Ks;   // Specular reflection coefficient
// uniform float shininessVal; // Shininess
// // Material color
// uniform vec3 ambientColor;
// uniform vec3 diffuseColor;
// uniform vec3 specularColor;
// uniform vec3 lightPos; // Light position

uniform float u_test;

uniform float u_Ns;

uniform vec3 u_Ka;
uniform vec3 u_Kd;
uniform vec3 u_Ks;

uniform float u_Ni;
uniform float u_d;
uniform float u_illu;


// uniform float u_test;

// void test(vec3 color)
// {
//   vec3 N = normalize(normalInterp);
//   vec3 L = normalize(lightPos - vertPos);

//   // Lambert's cosine law
//   float lambertian = max(dot(N, L), 0.0);
//   float specular = 0.0;
//   if(lambertian > 0.0) {
//     vec3 R = reflect(-L, N);      // Reflected light vector
//     vec3 V = normalize(-vertPos); // Vector to viewer
//     // Compute the specular term
//     float specAngle = max(dot(R, V), 0.0);
//     specular = pow(specAngle, shininessVal);
//   }
//   // gl_FragColor = vec4(Ka * ambientColor +
//   gl_FragColor = vec4(Ka * color +
//                       Kd * lambertian * diffuseColor +
//                       Ks * specular * specularColor, 1.0);

//   // only ambient
//   if(mode == 2) gl_FragColor = vec4(Ka * ambientColor, 1.0);
//   // only diffuse
//   if(mode == 3) gl_FragColor = vec4(Kd * lambertian * diffuseColor, 1.0);
//   // only specular
//   if(mode == 4) gl_FragColor = vec4(Ks * specular * specularColor, 1.0);

// 	return;
// }

void main()
{
  // colore = color * u_test ;

  // // Lambert's cosine law
  // float lambertian = 0.1;
  // float specular = 0.9;
  // if(lambertian > 0.0) {
  //   vec3 R = reflect(-L, N);      // Reflected light vector
  //   vec3 V = normalize(-vertPos); // Vector to viewer
  //   // Compute the specular term
  //   float specAngle = max(dot(R, V), 0.0);
  //   specular = pow(specAngle, shininessVal);
  // }
  // colore = vec3(u_Ka * color +
  //                     u_Kd * lambertian * color +
  //                     u_Ks * specular * color);

  colore = vec3(u_Ka * color);
}

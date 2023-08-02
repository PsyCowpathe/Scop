/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:02:09 by agirona           #+#    #+#             */
/*   Updated: 2023/08/02 17:13:01 by agirona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrice.hpp"

matrice::matrice()
{

}

matrice::~matrice()
{

}

std::vector<float>		matrice::multiply_mm(std::vector<float> m1, std::vector<float> m2)
{
	std::vector<float>	result(16, 0);
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (i * j < 16)
	{
		j = 0;
		while (j < 4)
		{
			result[(4 * i) + j] = m1[4 * i] * m2[0 + j] + m1[4 * i + 1] * m2[4 + j]
				+ m1[4 * i + 2] * m2[8 + j] + m1[4 * i + 3] * m2[12 + j];
			j++;
		}
		i++;
	}
	return (result);
}

std::vector<float>		matrice::multiply_mv(std::vector<float> matrice, std::vector<float> vector)
{
	std::vector<float>	result(4, 0);
	int					i;

	i = 0;
	while (i < 4)
	{
		result[i] = (matrice[4 * i] * vector[0] + matrice[4 * i + 1] * vector[1]
				+ matrice[4 * i + 2] * vector[2] + matrice[4 * i + 3] * vector[3]);
		i++;
	}
	/*if (result[3] != 0)
	{
		result[0] /= result[3];
		result[1] /= result[3];
		result[2] /= result[3];
	}*/
	return (result);
}



//=================================  PROJECTION  ==================================


/*std::vector<float>		matrice::create_projection_matrice(float width, float height)
{
	float VFOV = 45.0f;
	float tanHalfVFOV = tanf((VFOV / 2.0f) * (M_PI / 180));
	float d = 1/tanHalfVFOV;
	float ar = (float)width / (float)height;

	float NearZ = 1.0f;
	float FarZ = 10.0f;

	float zRange = NearZ - FarZ;

	float A = (-FarZ - NearZ) / zRange;
	float B = 2.0f * FarZ * NearZ / zRange;

	float proj[16] = {d/ar, 0.0f, 0.0f, 0.0f,
		0.0f, d,    0.0f, 0.0f,
		0.0f, 0.0f, A,    B,
		0.0f, 0.0f, 1.0f, 0.0f};

	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		matrice[i] = proj[i];
		i++;
	}
	return (matrice);
}

std::vector<float>		matrice::project(std::vector<float> to_project, float width, float height)
{
	std::vector<float>	projected(4, 0);
	std::vector<float>	matrice;
	int					i;

	if (to_project.size() != 4)
		return (projected);
	i = 0;
	matrice = create_projection_matrice(width, height);
	while (i < 4)
	{
		projected[i] = (matrice[4 * i] * to_project[0] + matrice[4 * i + 1] * to_project[1]
				+ matrice[4 * i + 2] * to_project[2] + matrice[4 * i + 3] * to_project[3]);
		i++;
	}
	if (projected[3] != 0)
	{
		projected[0] /= projected[3];
		projected[1] /= projected[3];
		projected[2] /= projected[3];
	}
	return (projected);
}*/

std::vector<float>		matrice::create_projection_matrice(float width, float height)
  {
  float	ar = height / width;
  float	fov = 60 * (M_PI / 180);
  float	znear = 0.00001f;
  float	zfar = 1000.0f;
  float	proj[16] = {ar * (1 / tanf(fov / 2)), 0, 0, 0, 
  0, 1 / tanf(fov / 2), 0, 0,
  0, 0, zfar / (zfar - znear), (-zfar * znear) / (zfar - znear),
  0, 0, 1, 0};
  std::vector<float>	matrice(16, 0);
  int					i;

  i = 0;
  while (i < 16)
  {
  matrice[i] = proj[i];
  i++;
  }
  return (matrice);
  }

  std::vector<float>		matrice::project(std::vector<float> to_project, float width, float height)
  {
  std::vector<float>	projected(4, 0);
  std::vector<float>	matrice;
  int					i;

  if (to_project.size() != 4)
  return (projected);
  i = 0;
  matrice = create_projection_matrice(width, height);
  while (i < 4)
  {
  projected[i] = (matrice[4 * i] * to_project[0] + matrice[4 * i + 1] * to_project[1]
  + matrice[4 * i + 2] * to_project[2] + matrice[4 * i + 3] * to_project[3]);
  i++;
  }
  if (projected[3] != 0)
  {
  projected[0] /= projected[3];
  projected[1] /= projected[3];
  projected[2] /= projected[3];
  }
  return (projected);
  }


//==================================  VIEW  ======================================


/*std::vector<float>			matrice::create_camera_matrice(std::vector<float> U, std::vector<float> V, std::vector<float> N, std::vector<float> CameraPos)
{
	float	view[16] = {U[0], U[1], U[2], -CameraPos[0],
		V[0], V[1], V[2], -CameraPos[1],
		N[0], N[1], N[2], -CameraPos[2],
		0.0f, 0.0f, 0.0f, 1.0f};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		matrice[i] = view[i];
		i++;
	}
	return (matrice);
}

std::vector<float>			matrice::camera(std::vector<float> U, std::vector<float> V, std::vector<float> N, std::vector<float> CameraPos, std::vector<float> to_view)
{
	std::vector<float>	viewed(4, 0);
	std::vector<float>	matrice;
	int					i;

	if (to_view.size() != 4)
		return (viewed);
	i = 0;
	matrice = create_camera_matrice(U, V, N, CameraPos);
	while (i < 4)
	{
		viewed[i] = (matrice[4 * i] * to_view[0] + matrice[4 * i + 1] * to_view[1]
				+ matrice[4 * i + 2] * to_view[2] + matrice[4 * i + 3] * to_view[3]);
		i++;
	}
	return (viewed);
}*/



std::vector<float>		matrice::normalize(std::vector<float> v)
  {
  float	norm;

  norm = sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
  v[0] /= norm;
  v[1] /= norm;
  v[2] /= norm;
  return (v);
  }

  std::vector<float>		matrice::cross(std::vector<float> v1, std::vector<float> v2)
  {
  std::vector<float>	product(3, 0);

  product[0] = v1[1] * v2[2] - v1[2] * v2[1];
  product[1] = v1[2] * v2[0] - v1[0] * v2[2];
  product[2] = v1[0] * v2[1] - v1[1] * v2[0];

  return (product);
  }

  float		matrice::dot(std::vector<float> v1, std::vector<float> v2)
  {
  float	res;

  res = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
  return (res);
  }

  std::vector<float>		matrice::create_view_matrice(std::vector<float> eye, std::vector<float> center, std::vector<float> up)
  {
  std::vector<float>	vx(4, 0);
  std::vector<float>	vy(4, 0);
  std::vector<float>	vz(4, 0);
  std::vector<float>	matrice(16, 0);
  int					i;

  vz[0] = eye[0] - center[0];
  vz[1] = eye[1] - center[1];
  vz[2] = eye[2] - center[2];
  vz = normalize(vz);
  vy[0] = up[0];
  vy[1] = up[1];
  vy[2] = up[2];
  vx = cross(vy, vz);
  vy = cross(vz, vx);
  vx = normalize(vx);
  vy = normalize(vy);

  float    buff[16] =
  {
  vx[0], vy[0], vz[0], 0.0f,
  vx[1], vy[1], vz[1], 0.0f,
  vx[2], vy[2], vz[2], 0.0f,
  -(dot(vx, eye)), -(dot(vy, eye)), -(dot(vz,eye)), 1.0f
  };
  i = 0;
  while (i < 16)
  {
  matrice[i] = buff[i];
  i++;
  }
  return (matrice);
  }


  std::vector<float>			matrice::view(std::vector<float> to_view, std::vector<float> eye, std::vector<float> center, std::vector<float> up)
  {
  std::vector<float>	viewed(4, 0);
  std::vector<float>	matrice;
int					i;

if (to_view.size() != 4)
	return (viewed);
	i = 0;
	matrice = create_view_matrice(eye, center, up);
while (i < 4)
{
	viewed[i] = (matrice[4 * i] * to_view[0] + matrice[4 * i + 1] * to_view[1]
			+ matrice[4 * i + 2] * to_view[2] + matrice[4 * i + 3] * to_view[3]);
	i++;
}
return (viewed);
}

/*std::vector<float>		matrice::create_view_matrice(float pitch, float yaw)
  {
  std::vector<float> 	dir(3, 0);
  std::vector<float> 	right(3, 0);
  std::vector<float> 	up(3, 0);	

  dir[0] = cosf(yaw * (M_PI / 180)) * cosf(pitch * (M_PI / 180));
  dir[1] = sinf(pitch * (M_PI / 180));
  dir[2] = sinf(yaw * (M_PI / 180)) * cosf(pitch * (M_PI / 180));
  dir = normalize(dir);

  right[0] = cosf(yaw * (M_PI / 180) - (M_PI / 2.0));
  right[1] = 0.0;
  right[2] = sinf(yaw * (M_PI / 180) - (M_PI / 2.0));

  up[0] = dir[1] * right[2] - dir[2] * right[1];
  up[1] = dir[2] * right[0] - dir[0] * right[2];
  up[2] = dir[0] * right[1] - dir[1] * right[0];
  up = normalize(up);

  float	view[16] = {right[0], right[1], right[2], -1,
  up[0], up[1], up[2], -1,
  dir[0], dir[1], dir[2], -1,
  0, 0, 0, 1};
  std::vector<float>	matrice(16, 0);
  int					i;

  i = 0;
  while (i < 16)
  {
  matrice[i] = view[i];
  i++;
  }
  return (matrice);
  }

  std::vector<float>		matrice::view(std::vector<float> to_view, float pitch, float yaw)
  {
  std::vector<float>	viewed(4, 0);
  std::vector<float>	matrice;
  int					i;

  if (to_view.size() != 4)
  return (viewed);
  i = 0;
  matrice = create_view_matrice(pitch, yaw);
  while (i < 4)
  {
  viewed[i] = (matrice[4 * i] * to_view[0] + matrice[4 * i + 1] * to_view[1]
  + matrice[4 * i + 2] * to_view[2] + matrice[4 * i + 3] * to_view[3]);
  i++;
  }
  return (viewed);

  }*/


//==================================  ROTATE  =====================================

std::vector<float>		matrice::create_rotate_matrice(char rotate, float angle)
{
	float	rot_x[16] = {1, 0, 0, 0, 0, cosf(angle), (sinf(angle) * -1), 0, 0, sinf(angle), cosf(angle), 0, 0, 0, 0, 1};
	float	rot_y[16] = {cosf(angle), 0, sinf(angle), 0, 0, 1, 0, 0, sinf(angle) * -1, 0, cosf(angle), 0, 0, 0, 0, 1};
	float	rot_z[16] = {cosf(angle), sinf(angle) * -1, 0, 0, sinf(angle), cosf(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		if (rotate == 'x')
			matrice[i] = rot_x[i];
		else if (rotate == 'y')
			matrice[i] = rot_y[i];
		else if (rotate == 'z')
			matrice[i] = rot_z[i];
		i++;
	}
	return (matrice);
}

std::vector<float>		matrice::rotate(std::vector<float> to_rotate, float angle, char rotate)
{
	std::vector<float>	rotated(4, 0);
	std::vector<float>	matrice;
	int					i;

	if (to_rotate.size() != 4 || angle < 0 || angle > 360)
		return (rotated);
	i = 0;
	matrice = create_rotate_matrice(rotate, angle *= (M_PI / 180));
	while (i < 4)
	{
		rotated[i] = (matrice[4 * i] * to_rotate[0] + matrice[4 * i + 1] * to_rotate[1]
				+ matrice[4 * i + 2] * to_rotate[2] + matrice[4 * i + 3] * to_rotate[3]);
		i++;
	}
	return (rotated);
}



//==================================  SCALE  =====================================

std::vector<float>		matrice::create_scale_matrice(std::vector<float> factor)
{
	float	scale[16] = {factor[0], 0, 0, 0, 0, factor[1], 0, 0, 0, 0, factor[2], 0, 0, 0, 0, 1};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		matrice[i] = scale[i];
		i++;
	}
	return (matrice);
}

std::vector<float>		matrice::scale(std::vector<float> to_scale, std::vector<float> factor)
{
	std::vector<float>	scaled(4, 0);
	std::vector<float>	matrice;
	int					i;

	if (to_scale.size() != 4 || factor.size() != 4)
		return (scaled);
	i = 0;
	matrice = create_scale_matrice(factor);
	while (i < 4)
	{
		scaled[i] = matrice[4 * i] * to_scale[0] + matrice[4 * i + 1] * to_scale[1]
			+ matrice[4 * i + 2] * to_scale[2] + matrice[4 * i + 3] * to_scale[3];
		i++;
	}
	return (scaled);
}



//================================  TRANSLATE  ===================================

std::vector<float>		matrice::create_translate_matrice(std::vector<float> to_add)
{
	float	trans[16] = {1, 0, 0, to_add[0], 0, 1, 0, to_add[1], 0, 0, 1, to_add[2], 0, 0, 0, 1};
	std::vector<float>	matrice(16, 0);
	int					i;

	i = 0;
	while (i < 16)
	{
		matrice[i] = trans[i];
		i++;
	}
	return (matrice);
}

std::vector<float>		matrice::translate(std::vector<float> to_translate, std::vector<float> to_add)
{
	std::vector<float>	translated(4, 0);
	std::vector<float>	matrice;

	if (to_add.size() != 4 || to_translate.size() != 4)
		return (translated);
	matrice = create_translate_matrice(to_add);
	translated[0] = matrice[3] + to_translate[0];
	translated[1] = matrice[7] + to_translate[1];
	translated[2] = matrice[11] + to_translate[2];
	translated[3] =	matrice[15] + to_translate[3];
	return (translated);
}

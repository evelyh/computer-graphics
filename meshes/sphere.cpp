#include "sphere.h"
#include <iostream>
#include <cmath>
#include <igl/PI.h>

void sphere(
    const int num_faces_u,
    const int num_faces_v,
    Eigen::MatrixXd &V,
    Eigen::MatrixXi &F,
    Eigen::MatrixXd &UV,
    Eigen::MatrixXi &UF,
    Eigen::MatrixXd &NV,
    Eigen::MatrixXi &NF)
{
  int num_vertices = (num_faces_u + 1) * (num_faces_v + 1);
  V.resize(num_vertices, 3);
  UV.resize(num_vertices, 2);
  NV.resize(num_vertices, 3);
  int row_index;

  for (int i = 0; i < num_faces_v + 1; i++)
  {
    for (int j = 0; j < num_faces_u + 1; j++)
    {
      row_index = i * num_faces_u + j;
      double v = (double)i / num_faces_v;
      double u = (double)j / num_faces_u;
      double t = 2 * v * igl::PI;
      double p = u * igl::PI;
      double x = sin(t) * sin(p);
      double y = -cos(p);
      double z = cos(t) * sin(p);

      V.row(row_index) = Eigen::RowVector3d(x, y, z);
      NV.row(row_index) = Eigen::RowVector3d(x, y, z);
      UV.row(row_index) = Eigen::RowVector2d(v, u);
    }
  }

  int num_faces = num_faces_u * num_faces_v;
  F.resize(num_faces, 4);
  UF.resize(num_faces, 4);
  NF.resize(num_faces, 4);

  for (int i = 0; i < num_faces_v; i++)
  {
    for (int j = 0; j < num_faces_u; j++)
    {
      row_index = i * num_faces_u + j;
      int a = i * (num_faces_u + 1) + j;
      int b = i * (num_faces_u + 1) + j + 1;
      int c = (i + 1) * (num_faces_u + 1) + j + 1;
      int d = (i + 1) * (num_faces_u + 1) + j;

      F.row(row_index) = Eigen::RowVector4i(a, b, c, d);
      UF.row(row_index) = Eigen::RowVector4i(a, b, c, d);
      NF.row(row_index) = Eigen::RowVector4i(a, b, c, d);
    }
  }
}

#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <igl/PI.h>

void per_corner_normals(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    const double corner_threshold,
    Eigen::MatrixXd &N)
{
  N = Eigen::MatrixXd::Zero(F.rows() * 3, 3);

  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  Eigen::RowVector3d a, b, c, n1, n2;

  for (int i = 0; i < F.rows(); i++)
  {
    a = V.row(F(i, 0));
    b = V.row(F(i, 1));
    c = V.row(F(i, 2));
    n1 = triangle_area_normal(a, b, c);

    for (int j = 0; j < F.cols(); j++)
    {
      Eigen::RowVector3d normal(0, 0, 0);
      for (int k = 0; k < VF[F(i, j)].size(); k++)
      {
        a = V.row(F(k, 0));
        b = V.row(F(k, 1));
        c = V.row(F(k, 2));
        n2 = triangle_area_normal(a, b, c);

        if (n1.normalized().dot(n2.normalized()) > cos(corner_threshold * igl::PI / 180.0))
        {
          normal += n2;
        }
      }

      N.row(i * 3 + j) = normal.normalized();
    }
  }
}

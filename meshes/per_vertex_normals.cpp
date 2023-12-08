#include "per_vertex_normals.h"
#include "triangle_area_normal.h"

void per_vertex_normals(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    Eigen::MatrixXd &N)
{
  N = Eigen::MatrixXd::Zero(V.rows(), 3);

  Eigen::RowVector3d a, b, c;

  for (int i = 0; i < V.rows(); i++)
  {
    Eigen::RowVector3d normal(0, 0, 0);
    for (int j = 0; j < F.rows(); j++)
    {
      a = V.row(F(j, 0));
      b = V.row(F(j, 1));
      c = V.row(F(j, 2));
      normal += triangle_area_normal(a, b, c);
    }
    N.row(i) = normal.normalized();
  }
}

#include "linear_blend_skinning.h"

void linear_blend_skinning(
    const Eigen::MatrixXd &V,
    const Skeleton &skeleton,
    const std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d>> &T,
    const Eigen::MatrixXd &W,
    Eigen::MatrixXd &U)
{
  U.resize(V.rows(), 3);

  for (int i = 0; i < V.rows(); i++)
  {
    Eigen::Vector4d deformed_position = Eigen::Vector4d::Zero();

    for (int j = 0; j < skeleton.size(); j++)
    {
      if (skeleton[j].weight_index >= 0)
      {
        Eigen::Vector4d homogenous_vertex(V(i, 0), V(i, 1), V(i, 2), 1);
        deformed_position += W(i, skeleton[j].weight_index) * (T[j] * homogenous_vertex);
      }
    }

    for (int h = 0; h < 3; h++)
    {
      U(i, h) = deformed_position(h);
    }
  }
}

#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
    const Skeleton &skeleton,
    const Eigen::VectorXi &b)
{
  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d>> T;
  Eigen::VectorXd ret = Eigen::VectorXd::Zero(3 * b.size());
  forward_kinematics(skeleton, T);

  for (int i = 0; i < b.size(); i++)
  {
    Eigen::Vector4d len;
    len << skeleton[b[i]].length, 0, 0, 1;
    Eigen::VectorXd curr = T[b[i]] * skeleton[b[i]].rest_T * len;

    for (int j = 0; j < 3; j++)
    {
      ret[3 * i + j] = curr[j];
    }
  }

  return ret;
}

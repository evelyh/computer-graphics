#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
    const Skeleton &skeleton,
    const Eigen::VectorXi &b,
    Eigen::MatrixXd &J)
{
  J = Eigen::MatrixXd::Zero(b.size() * 3, skeleton.size() * 3);
  Skeleton copy = skeleton;
  Eigen::VectorXd position = transformed_tips(skeleton, b);
  Eigen::VectorXd temp_p;

  for (int i = 0; i < skeleton.size(); i++)
  {
    for (int j = 0; j < 3; j++)
    {
      copy[i].xzx(j) += 1e-6;
      temp_p = transformed_tips(copy, b);
      J.col(i * 3 + j) = (temp_p - position) / 1e-6;
      copy[i].xzx(j) -= 1e-6;
    }
  }
}

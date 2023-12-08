#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
    const Skeleton &skeleton,
    const Eigen::VectorXi &b,
    const Eigen::VectorXd &xb0,
    std::function<double(const Eigen::VectorXd &)> &f,
    std::function<Eigen::VectorXd(const Eigen::VectorXd &)> &grad_f,
    std::function<void(Eigen::VectorXd &)> &proj_z)
{
  // https://eigen.tuxfamily.org/dox/classEigen_1_1MatrixBase.html#ac8da566526419f9742a6c471bbd87e0a

  f = [&](const Eigen::VectorXd &A) -> double
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd position = transformed_tips(copy, b);
    return (position - xb0).squaredNorm();
  };
  grad_f = [&](const Eigen::VectorXd &A) -> Eigen::VectorXd
  {
    Eigen::MatrixXd J;
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd position = transformed_tips(copy, b);

    kinematics_jacobian(copy, b, J);
    Eigen::VectorXd df;
    df = J.transpose() * (2 * (position - xb0));

    return df;
  };
  proj_z = [&](Eigen::VectorXd &A)
  {
    assert(skeleton.size() * 3 == A.size());
    for (int i = 0; i < skeleton.size(); i++)
    {
      for (int j = 0; j < 3; j++)
      {
        A(i * 3 + j) = std::fmax(skeleton[i].xzx_min(j), std::fmin(skeleton[i].xzx_max(j), A(i * 3 + j)));
      }
    }
  };
}

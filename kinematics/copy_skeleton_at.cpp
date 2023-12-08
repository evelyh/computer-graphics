#include "copy_skeleton_at.h"
Skeleton copy_skeleton_at(
    const Skeleton &skeleton,
    const Eigen::VectorXd &A)
{
  Skeleton copy = skeleton;

  for (int i = 0; i < skeleton.size(); i++)
  {
    for (int j = 0; j < 3; j++)
      copy[i].xzx(j) = A(3 * i + j);
  }
  return copy;
}

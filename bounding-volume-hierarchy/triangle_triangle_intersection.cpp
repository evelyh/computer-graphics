#include "triangle_triangle_intersection.h"

bool triangle_triangle_intersection(
    const Eigen::RowVector3d &A0,
    const Eigen::RowVector3d &A1,
    const Eigen::RowVector3d &A2,
    const Eigen::RowVector3d &B0,
    const Eigen::RowVector3d &B1,
    const Eigen::RowVector3d &B2)
{
  for (int i = 0; i < 3; i++)
  {
    double a_min = std::min({A0(i), A1(i), A2(i)});
    double a_max = std::max({A0(i), A1(i), A2(i)});
    double b_min = std::min({B0(i), B1(i), B2(i)});
    double b_max = std::max({B0(i), B1(i), B2(i)});
    if (a_max < b_min || b_max < a_min)
      return false;
  }
  return true;
}

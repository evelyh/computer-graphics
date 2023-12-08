#include "line_search.h"
#include <iostream>

double line_search(
    const std::function<double(const Eigen::VectorXd &)> &f,
    const std::function<void(Eigen::VectorXd &)> &proj_z,
    const Eigen::VectorXd &z,
    const Eigen::VectorXd &dz,
    const double max_step)
{
  double alpha = max_step;
  double f0 = f(z);
  double f_ls;
  double threshold = 1e-4;
  Eigen::VectorXd z_ls;

  while (alpha > threshold)
  {
    z_ls = z - alpha * dz;
    proj_z(z_ls);
    f_ls = f(z_ls);

    if (f_ls < f0)
      return alpha;
    alpha *= 0.5;
  }

  return alpha;
}

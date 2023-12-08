#include "fast_mass_springs_step_dense.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_dense(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &E,
    const double k,
    const Eigen::VectorXi &b,
    const double delta_t,
    const Eigen::MatrixXd &fext,
    const Eigen::VectorXd &r,
    const Eigen::MatrixXd &M,
    const Eigen::MatrixXd &A,
    const Eigen::MatrixXd &C,
    const Eigen::LLT<Eigen::MatrixXd> &prefactorization,
    const Eigen::MatrixXd &Uprev,
    const Eigen::MatrixXd &Ucur,
    Eigen::MatrixXd &Unext)
{
  Eigen::MatrixXd y = M / (delta_t * delta_t) * (2 * Ucur - Uprev) + fext + 1e10 * C.transpose() * C * V;

  Unext.resize(Ucur.rows(), Ucur.cols());

  Eigen::MatrixXd d = Eigen::MatrixXd::Zero(E.rows(), 3);
  Eigen::MatrixXd l = Eigen::MatrixXd::Zero(E.rows(), 3);

  for (int i = 0; i < 50; i++)
  {
    for (int j = 0; j < E.rows(); j++)
    {
      d.row(j) = (Unext.row(E(j, 0)) - Unext.row(E(j, 1))).normalized() * r(j);
    }
    l = k * A.transpose() * d + y;
    Unext = prefactorization.solve(l);
  }
}

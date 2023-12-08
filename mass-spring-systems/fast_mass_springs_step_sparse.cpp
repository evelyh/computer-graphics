#include "fast_mass_springs_step_sparse.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_sparse(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &E,
    const double k,
    const Eigen::VectorXi &b,
    const double delta_t,
    const Eigen::MatrixXd &fext,
    const Eigen::VectorXd &r,
    const Eigen::SparseMatrix<double> &M,
    const Eigen::SparseMatrix<double> &A,
    const Eigen::SparseMatrix<double> &C,
    const Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> &prefactorization,
    const Eigen::MatrixXd &Uprev,
    const Eigen::MatrixXd &Ucur,
    Eigen::MatrixXd &Unext)
{
  Eigen::MatrixXd y = M / (delta_t * delta_t) * (2 * Ucur - Uprev) + fext + 1e10 * C.transpose() * C * V;

  Unext.resize(Ucur.rows(), Ucur.cols());

  Eigen::MatrixXd d(E.rows(), 3);
  Eigen::MatrixXd l(V.rows(), 3);

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

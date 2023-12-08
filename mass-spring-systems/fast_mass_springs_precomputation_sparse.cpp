#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &E,
    const double k,
    const Eigen::VectorXd &m,
    const Eigen::VectorXi &b,
    const double delta_t,
    Eigen::VectorXd &r,
    Eigen::SparseMatrix<double> &M,
    Eigen::SparseMatrix<double> &A,
    Eigen::SparseMatrix<double> &C,
    Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> &prefactorization)
{
  std::vector<Eigen::Triplet<double>> temp;

  r.resize(E.rows());
  for (int i = 0; i < E.rows(); i++)
  {
    r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
  }

  for (int i = 0; i < V.rows(); i++)
  {
    temp.emplace_back(i, i, m(i));
  }

  M.resize(V.rows(), V.rows());
  M.setFromTriplets(temp.begin(), temp.end());

  signed_incidence_matrix_sparse(V.rows(), E, A);

  temp.clear();
  for (int i = 0; i < b.rows(); i++)
  {
    temp.emplace_back(i, b(i), 1);
  }

  C.resize(b.rows(), V.rows());
  C.setFromTriplets(temp.begin(), temp.end());

  Eigen::SparseMatrix<double> Q = k * A.transpose() * A + M / (delta_t * delta_t) + 1e10 * C.transpose() * C;

  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}

#include "signed_incidence_matrix_sparse.h"
#include <vector>

void signed_incidence_matrix_sparse(
    const int n,
    const Eigen::MatrixXi &E,
    Eigen::SparseMatrix<double> &A)
{
  std::vector<Eigen::Triplet<double>> temp;
  for (int i = 0; i < E.rows(); i++)
  {
    temp.emplace_back(i, E(i, 0), 1);
    temp.emplace_back(i, E(i, 1), -1);
  }

  A.resize(E.rows(), n);
  A.setFromTriplets(temp.begin(), temp.end());
}

#include "cube.h"

void cube(
    Eigen::MatrixXd &V,
    Eigen::MatrixXi &F,
    Eigen::MatrixXd &UV,
    Eigen::MatrixXi &UF,
    Eigen::MatrixXd &NV,
    Eigen::MatrixXi &NF)
{
  V.resize(8, 3); // eight vertex
  V << 0, 0, 0,   // 0
      1, 0, 0,
      1, 1, 0,
      0, 1, 0,
      0, 0, 1, // 4
      1, 0, 1,
      1, 1, 1,
      0, 1, 1; // 7

  F.resize(6, 4); // six faces each defined by four vertex
  F << 1, 2, 5, 6,
      0, 1, 2, 4,
      2, 4, 6, 7,
      3, 5, 6, 7,
      0, 3, 4, 7,
      0, 1, 3, 5;

  UV.resize(14, 2); // 2d vertex
  UV << 0, 0.5,     // 0
      0, 0.25,
      0.25, 0.75,
      0.25, 0.5,
      0.25, 0.25,
      0.25, 0, // 5
      0.5, 0.75,
      0.5, 0.5,
      0.5, 0.25,
      0.5, 0,
      0.75, 0.5, // 10
      0.75, 0.25,
      1, 0.5,
      1, 0.25; // 13

  UF.resize(6, 4); // 2d face
  UF << 0, 1, 3, 4,
      2, 3, 6, 7,
      3, 4, 7, 8,
      4, 5, 8, 9,
      7, 8, 10, 11,
      10, 11, 12, 13;

  NV.resize(6, 3); // normal vector
  NV << 0, 1, 0,
      1, 0, 0,
      0, 0, 1,
      -1, 0, 0,
      0, 0, -1,
      0, -1, 0;

  NF.resize(6, 4); // normal face
  NF << 0, 0, 0, 0,
      1, 1, 1, 1,
      2, 2, 2, 2,
      3, 3, 3, 3,
      4, 4, 4, 4,
      5, 5, 5, 5;
}

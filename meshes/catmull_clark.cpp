#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <vector>
#include <map>

void construct_quad_faces(
    Eigen::MatrixXd &SV,
    Eigen::MatrixXi &SF,
    const Eigen::RowVector3d &a,
    const Eigen::RowVector3d &b,
    const Eigen::RowVector3d &c,
    const Eigen::RowVector3d &d)
{
  int v0 = SV.rows();
  SV.resize(v0 + 4, Eigen::NoChange);
  SV.row(v0) = a;
  SV.row(v0 + 1) = b;
  SV.row(v0 + 2) = c;
  SV.row(v0 + 3) = d;
  SF.resize(SF.rows() + 1, Eigen::NoChange);
  SF.row(SF.rows() - 1) << v0, v0 + 1, v0 + 2, v0 + 3;
}

void catmull_clark(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    const int num_iters,
    Eigen::MatrixXd &SV,
    Eigen::MatrixXi &SF)
{
  // base case, no iteration
  if (num_iters <= 0)
  {
    SV = V;
    SF = F;
    return;
  }

  int num_verts = V.rows();
  int num_faces = F.rows();

  std::map<std::pair<int, int>, int> edge_to_vertex;
  std::vector<Eigen::RowVector3d> face_points(num_faces, Eigen::RowVector3d::Zero());
  std::vector<int> valence(num_verts, 0);
  std::vector<std::vector<int>> vertex_faces(num_verts, std::vector<int>());

  // compute face points and update vertex valence
  for (int i = 0; i < num_faces; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      int v = F(i, j);
      int next_v = F(i, (j + 1) % 4);
      valence[v]++;
      vertex_faces[v].push_back(i);
      auto edge = std::make_pair(v, next_v);
      if (edge_to_vertex.find(edge) == edge_to_vertex.end())
      {
        int new_vertex = SV.rows();
        edge_to_vertex[edge] = new_vertex;
        SV.resize(new_vertex + 1, Eigen::NoChange);
        SV.row(new_vertex) = (V.row(v) + V.row(next_v) + face_points[i] + face_points[i]) / 4.0;
      }
    }
    face_points[i] = (V.row(F(i, 0)) + V.row(F(i, 1)) + V.row(F(i, 2)) + V.row(F(i, 3))) / 4.0;
  }

  // update vertex positions
  Eigen::MatrixXd new_vertex_positions(num_verts, 3);
  for (int v = 0; v < num_verts; v++)
  {
    Eigen::RowVector3d Q(0, 0, 0);
    for (int f : vertex_faces[v])
    {
      Q += face_points[f];
    }
    Q /= valence[v];

    Eigen::RowVector3d R(0, 0, 0);
    for (int j = 0; j < valence[v]; j++)
    {
      R += (V.row(F(vertex_faces[v][j], 0)) +
            V.row(F(vertex_faces[v][j], 1)) +
            V.row(F(vertex_faces[v][j], 2)) +
            V.row(F(vertex_faces[v][j], 3)));
    }
    R /= (valence[v] * valence[v]);

    new_vertex_positions.row(v) = (Q + 2.0 * R + (valence[v] - 3.0) * V.row(v)) / valence[v];
  }

  // construct the new faces
  int num_new_faces = num_faces * 4;
  SF.resize(num_new_faces, 4);
  SV.resize(num_verts + edge_to_vertex.size(), 3);
  SV.topRows(num_verts) = new_vertex_positions;
  for (int i = 0; i < num_faces; i++)
  {
    int v0 = F(i, 0);
    int v1 = F(i, 1);
    int v2 = F(i, 2);
    int v3 = F(i, 3);
    int w01 = edge_to_vertex[std::make_pair(v0, v1)];
    int w12 = edge_to_vertex[std::make_pair(v1, v2)];
    int w23 = edge_to_vertex[std::make_pair(v2, v3)];
    int w30 = edge_to_vertex[std::make_pair(v3, v0)];

    construct_quad_faces(SV, SF, V.row(v0), SV.row(w01), face_points[i], SV.row(w30));
    construct_quad_faces(SV, SF, SV.row(w01), V.row(v1), SV.row(w12), face_points[i]);
    construct_quad_faces(SV, SF, face_points[i], SV.row(w12), V.row(v2), SV.row(w23));
    construct_quad_faces(SV, SF, SV.row(w30), face_points[i], SV.row(w23), V.row(v3));
  }

  catmull_clark(SV, SF, num_iters - 1, SV, SF);
}

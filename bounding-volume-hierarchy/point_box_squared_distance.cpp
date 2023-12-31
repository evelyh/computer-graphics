#include "point_box_squared_distance.h"

double point_box_squared_distance(
    const Eigen::RowVector3d &query,
    const BoundingBox &box)
{
  double dis_x = std::max({box.min_corner(0) - query(0), query(0) - box.max_corner(0), 0.0});
  double dis_y = std::max({box.min_corner(1) - query(1), query(1) - box.max_corner(1), 0.0});
  double dis_z = std::max({box.min_corner(2) - query(2), query(2) - box.max_corner(2), 0.0});

  return (pow(dis_x, 2) + pow(dis_y, 2) + pow(dis_z, 2));
}

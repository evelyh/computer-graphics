#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
    const Ray &ray,
    const BoundingBox &box,
    const double min_t,
    const double max_t)
{
  double t_min, t_max, tmp_min, tmp_max;
  for (int i = 0; i < 3; i++)
  {
    if (ray.direction(i) >= 0)
    {
      tmp_min = (box.min_corner(i) - ray.origin(i)) / ray.direction(i);
      tmp_max = (box.max_corner(i) - ray.origin(i)) / ray.direction(i);
    }
    else
    {
      tmp_min = (box.max_corner(i) - ray.origin(i)) / ray.direction(i);
      tmp_max = (box.min_corner(i) - ray.origin(i)) / ray.direction(i);
    }
    if (tmp_min < t_min)
      t_min = tmp_min;
    if (tmp_max > t_max)
      t_max = tmp_max;
  }

  return (t_min <= t_max && std::max(min_t, t_min) <= std::min(max_t, t_max));
}

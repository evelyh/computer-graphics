#include "first_hit.h"

bool first_hit(
    const Ray &ray,
    const double min_t,
    const std::vector<std::shared_ptr<Object>> &objects,
    int &hit_id,
    double &t,
    Eigen::Vector3d &n)
{
  bool hit_found = false;

  t = -1;
  double temp_t;
  Eigen::Vector3d temp_n;

  for (int i = 0; i < objects.size(); i++)
  {
    auto &obj = objects[i];

    if (obj->intersect(ray, min_t, temp_t, temp_n))
    {
      if (t == -1 || temp_t < t)
      {
        t = temp_t; // update parametric distance
        n = temp_n; // update surface normal
        hit_id = i;
        hit_found = true;
      }
    }
  }
  return hit_found;
}
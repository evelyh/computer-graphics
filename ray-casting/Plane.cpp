#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
    const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
  n = this->normal;

  // orthogonal to plane normal, parallel with plane
  if (n.dot(ray.direction) == 0)
    return false;

  // how aligned the point on plane is from the ray / unit vector of the ray
  // = the distance of the intersection point on the ray
  t = n.dot(this->point - ray.origin) / (n.dot(ray.direction));

  return (t >= min_t);
}

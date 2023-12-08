#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
    const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
  double a = ray.direction.dot(ray.direction);
  double b = 2 * ray.direction.dot(ray.origin - this->center);
  double c = (ray.origin - this->center).dot(ray.origin - this->center) - pow(this->radius, 2);
  double delta = pow(b, 2) - 4 * a * c;

  if (delta < 0)
  {
    return false;
  }

  double st = (-b - sqrt(delta)) / (2 * a); // smaller t
  double lt = (-b + sqrt(delta)) / (2 * a); // larger t

  if (lt < min_t) // both < min_t
  {
    return false;
  }
  else // lt >= min_t
  {
    if (st < min_t)
    {
      t = lt;
    }
    else
    { // both >= min_t, choose closer one
      t = st;
    }
  }

  n = (ray.origin + t * ray.direction - this->center).normalized();

  return true;
}

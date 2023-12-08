#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
    const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
  Eigen::Vector3d A = std::get<0>(corners);
  Eigen::Vector3d B = std::get<1>(corners);
  Eigen::Vector3d C = std::get<2>(corners);
  Eigen::Vector3d e1 = B - A;
  Eigen::Vector3d e2 = C - A;
  n = e1.cross(e2).normalized();

  // linear system in Cramer's rule
  double a = A.x() - B.x();
  double b = A.y() - B.y();
  double c = A.z() - B.z();
  double d = A.x() - C.x();
  double e = A.y() - C.y();
  double f = A.z() - C.z();
  double g = ray.direction.x();
  double h = ray.direction.y();
  double i = ray.direction.z();
  double j = A.x() - ray.origin.x();
  double k = A.y() - ray.origin.y();
  double l = A.z() - ray.origin.z();

  auto helper = [](double x, double y, double u, double v)
  {
    return (x * y - u * v);
  };

  double M = a * helper(e, i, h, f) + b * helper(g, f, d, i) + c * helper(d, h, e, g);

  double beta = (j * helper(e, i, h, f) + k * helper(g, f, d, i) + l * helper(d, h, e, g)) / M;

  double alpha = (i * helper(a, k, j, b) + h * helper(j, c, a, l) + g * helper(b, l, k, c)) / M;

  t = -(f * helper(a, k, j, b) + e * helper(j, c, a, l) + d * helper(b, l, k, c)) / M;

  if (t < min_t)
    return false;

  if (alpha < 0 || alpha > 1)
    return false;

  if (beta < 0 || beta > (1 - alpha))
    return false;

  return true;
}

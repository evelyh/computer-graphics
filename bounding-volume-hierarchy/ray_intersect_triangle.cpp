#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
    const Ray &ray,
    const Eigen::RowVector3d &A,
    const Eigen::RowVector3d &B,
    const Eigen::RowVector3d &C,
    const double min_t,
    const double max_t,
    double &t)
{
  Eigen::RowVector3d e1 = B - A;
  Eigen::RowVector3d e2 = C - A;

  // linear system in Cramer's rule
  double a = A(0) - B(0);
  double b = A(1) - B(1);
  double c = A(2) - B(2);
  double d = A(0) - C(0);
  double e = A(1) - C(1);
  double f = A(2) - C(2);
  double g = ray.direction(0);
  double h = ray.direction(1);
  double i = ray.direction(2);
  double j = A(0) - ray.origin(0);
  double k = A(1) - ray.origin(1);
  double l = A(2) - ray.origin(2);

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

#include "viewing_ray.h"

void viewing_ray(
    const Camera &camera,
    const int i,
    const int j,
    const int width,
    const int height,
    Ray &ray)
{
  // pixel index related to image width and height

  double u = (camera.width / width * (j + 0.5)) - (camera.width * 0.5);
  // row index decrease from top to bottom
  double v = -(camera.height / height * (i + 0.5)) + camera.height * 0.5;

  // direction = -c.d * c.w + u * c.u + v * c.v
  ray.origin = camera.e;
  ray.direction = (-camera.d * camera.w + u * camera.u + v * camera.v).normalized();
}

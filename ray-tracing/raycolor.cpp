
#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
    const Ray &ray,
    const double min_t,
    const std::vector<std::shared_ptr<Object>> &objects,
    const std::vector<std::shared_ptr<Light>> &lights,
    const int num_recursive_calls,
    Eigen::Vector3d &rgb)
{
  if (num_recursive_calls > 5)
    return false;

  rgb = Eigen::Vector3d(0, 0, 0);
  int ray_hit_id;
  double ray_t;
  Eigen::Vector3d ray_n;

  if (first_hit(ray, min_t, objects, ray_hit_id, ray_t, ray_n))
  {
    rgb += blinn_phong_shading(ray, ray_hit_id, ray_t, ray_n, objects, lights);

    Ray mirror_ray;
    mirror_ray.direction = reflect(ray.direction, ray_n);
    mirror_ray.origin = ray.origin + ray_t * ray.direction;

    Eigen::Vector3d mirror_rgb;
    if (raycolor(mirror_ray, 0.00001, objects, lights, num_recursive_calls + 1, mirror_rgb))
    {
      rgb += ((objects[ray_hit_id]->material->km).array() * mirror_rgb.array()).matrix();
    }

    return true;
  }

  return false;
}

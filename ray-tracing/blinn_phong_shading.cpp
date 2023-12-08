#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <cmath>

Eigen::Vector3d blinn_phong_shading(
    const Ray &ray,
    const int &hit_id,
    const double &t,
    const Eigen::Vector3d &n,
    const std::vector<std::shared_ptr<Object>> &objects,
    const std::vector<std::shared_ptr<Light>> &lights)
{
  // intersection
  Eigen::Vector3d p = ray.origin + t * ray.direction;
  Eigen::Vector3d rgb(0, 0, 0);

  Eigen::Vector3d ka = objects[hit_id]->material->ka;
  Eigen::Vector3d kd = objects[hit_id]->material->kd;
  Eigen::Vector3d ks = objects[hit_id]->material->ks;
  double phong = objects[hit_id]->material->phong_exponent;

  rgb += (ka.array() * 0.1).matrix();

  // light direction vector
  Eigen::Vector3d l;
  double max_t;

  // check first_hit
  Ray shadow_ray;
  int ray_hit_id;
  double ray_t;
  Eigen::Vector3d ray_n;

  for (auto &light : lights)
  {
    light->direction(p, l, max_t);
    shadow_ray.origin = p;
    shadow_ray.direction = l;

    if ((!first_hit(shadow_ray, 0.00001, objects, ray_hit_id, ray_t, ray_n)) || ray_t > max_t)
    {
      Eigen::Vector3d half = (-ray.direction.normalized() + l).normalized();
      Eigen::Vector3d light_color = light->I;
      rgb += (kd.array() * light_color.array() * std::fmax(0, n.dot(l))).matrix();
      rgb += (ks.array() * light_color.array() * std::pow(std::fmax(0, n.dot(half)), phong)).matrix();
    }
  }

  return rgb;
}
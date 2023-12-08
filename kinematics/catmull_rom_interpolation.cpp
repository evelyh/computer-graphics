#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>
#include <vector>
#include <algorithm>

Eigen::Vector3d catmull_rom_interpolation(
    const std::vector<std::pair<double, Eigen::Vector3d>> &keyframes, double t)
{
  if (keyframes.size() == 0)
    return Eigen::Vector3d::Zero();

  double t_0, t_1, t_2, t_3;
  Eigen::Vector3d p_0, p_1, p_2, p_3, d_0, d_2;

  const double looped_time = std::fmod(t, keyframes.back().first);
  int index = 0;
  for (int i = 0; i < keyframes.size() - 1; i++)
  {
    if (keyframes[i].first <= looped_time && looped_time < keyframes[i + 1].first)
    {
      index = i;
      break;
    }
  }
  int offset = (index == 0) ? 0 : 1;

  t_0 = keyframes[index - offset].first;
  p_0 = keyframes[index - offset].second;
  t_1 = keyframes[index].first;
  p_1 = keyframes[index].second;
  t_2 = keyframes[index + 1].first;
  p_2 = keyframes[index + 1].second;
  t_3 = keyframes[index + 2].first;
  p_3 = keyframes[index + 2].second;

  d_0 = (p_2 - p_0) / (t_2 - t_0);
  d_2 = (p_3 - p_1) / (t_3 - t_1);

  double norm_time = (looped_time - t_1) / (t_2 - t_1);
  Eigen::Vector3d result(0, 0, 0);
  result = (2 * pow(norm_time, 3) - 3 * pow(norm_time, 2) + 1) * p_1 +
           (pow(norm_time, 3) - 2 * pow(norm_time, 2) + norm_time) * d_0 +
           (-2 * pow(norm_time, 3) + 3 * pow(norm_time, 2)) * p_2 +
           (pow(norm_time, 3) - pow(norm_time, 2)) * d_2;

  return result;
}
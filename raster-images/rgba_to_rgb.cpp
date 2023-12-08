#include "rgba_to_rgb.h"

void rgba_to_rgb(
    const std::vector<unsigned char> &rgba,
    const int &width,
    const int &height,
    std::vector<unsigned char> &rgb)
{
  rgb.resize(height * width * 3);

  for (int i = 0, j = 0; i < rgba.size(); i += 4, j += 3)
  {
    for (int h = 0; h < 3; h++)
    {
      // new rgb value == org rgb * alpha
      rgb[j + h] = rgba[i + h] * rgba[i + 3] / 255.0;
    }
  }
}

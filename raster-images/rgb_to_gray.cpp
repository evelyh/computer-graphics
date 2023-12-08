#include "rgb_to_gray.h"

void rgb_to_gray(
    const std::vector<unsigned char> &rgb,
    const int width,
    const int height,
    std::vector<unsigned char> &gray)
{
  gray.resize(height * width);
  int i = 0;

  for (int h = 0; h < rgb.size(); h += 3)
  {
    gray[i++] = rgb[h] * 0.2126 + rgb[h + 1] * 0.7152 + rgb[h + 2] * 0.0722;
  }
}

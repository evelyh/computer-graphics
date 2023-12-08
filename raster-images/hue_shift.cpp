#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
    const std::vector<unsigned char> &rgb,
    const int width,
    const int height,
    const double shift,
    std::vector<unsigned char> &shifted)
{
  shifted.resize(rgb.size());

  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      int pixel = (row * width + col) * 3;
      double r = rgb[pixel];
      double g = rgb[pixel + 1];
      double b = rgb[pixel + 2];
      double h, s, v;

      rgb_to_hsv(r, g, b, h, s, v);
      // neg values shift clockwise around the color wheel
      h = fmod(h + shift + 360, 360);
      hsv_to_rgb(h, s, v, r, g, b);

      shifted[pixel] = r;
      shifted[pixel + 1] = g;
      shifted[pixel + 2] = b;
    }
  }
}

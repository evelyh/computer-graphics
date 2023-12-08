#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
    const std::vector<unsigned char> &rgb,
    const int width,
    const int height,
    const double factor,
    std::vector<unsigned char> &desaturated)
{
  desaturated.resize(rgb.size());

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
      s -= factor * s;
      hsv_to_rgb(h, s, v, r, g, b);

      desaturated[pixel] = r;
      desaturated[pixel + 1] = g;
      desaturated[pixel + 2] = b;
    }
  }
}

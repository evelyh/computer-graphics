#include "demosaic.h"

#include <cmath>

void demosaic(
    const std::vector<unsigned char> &bayer,
    const int &width,
    const int &height,
    std::vector<unsigned char> &rgb)
{
  rgb.resize(width * height * 3);

  double r, g, b;
  int MAX = std::max(width, height) + 1;

  auto pixel = [width](int col, int row)
  {
    return width * row + col;
  };

  auto neigh_avg = [bayer, pixel, width, height](int a, int b, int c, int d, int e, int f, int g, int h)
  {
    int cnt = 0;
    int sum = 0;
    if (a >= 0 && a < width && b >= 0 && b < height)
    {
      cnt++;
      sum += bayer[pixel(a, b)];
    }
    if (c >= 0 && c < width && d >= 0 && d < height)
    {
      cnt++;
      sum += bayer[pixel(c, d)];
    }
    if (e >= 0 && e < width && f >= 0 && f < height)
    {
      cnt++;
      sum += bayer[pixel(e, f)];
    }
    if (g >= 0 && g < width && h >= 0 && h < height)
    {
      cnt++;
      sum += bayer[pixel(g, h)];
    }
    return static_cast<double>(sum / cnt);
  };

  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      if (col % 2 == 0 && row % 2 == 0)
      { // first green
        r = neigh_avg(col, row - 1, col, row + 1, MAX, MAX, MAX, MAX);
        g = bayer[pixel(col, row)];
        b = neigh_avg(col - 1, row, col + 1, row, MAX, MAX, MAX, MAX);
      }
      else if (col % 2 == 1 && row % 2 == 0)
      { // blue
        r = neigh_avg(col - 1, row - 1, col + 1, row - 1, col - 1, row + 1, col + 1, row + 1);
        g = neigh_avg(col - 1, row, col + 1, row, col, row - 1, col, row + 1);
        b = bayer[pixel(col, row)];
      }
      else if (col % 2 == 0 && row % 2 == 1)
      { // red
        r = bayer[pixel(col, row)];
        g = neigh_avg(col - 1, row, col + 1, row, col, row - 1, col, row + 1);
        b = neigh_avg(col - 1, row - 1, col + 1, row - 1, col - 1, row + 1, col + 1, row + 1);
      }
      else
      { // second green
        r = neigh_avg(col - 1, row, col + 1, row, MAX, MAX, MAX, MAX);
        g = bayer[pixel(col, row)];
        b = neigh_avg(col, row - 1, col, row + 1, MAX, MAX, MAX, MAX);
      }

      rgb[pixel(col, row) * 3] = static_cast<unsigned char>(r);
      rgb[pixel(col, row) * 3 + 1] = static_cast<unsigned char>(g);
      rgb[pixel(col, row) * 3 + 2] = static_cast<unsigned char>(b);
    }
  }
}
#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
    const std::vector<unsigned char> &rgb,
    const int &width,
    const int &height,
    std::vector<unsigned char> &bayer)
{
  bayer.resize(width * height);

  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      int pixel = row * width + col;

      // store red
      if (row % 2 == 1 && col % 2 == 0)
      {
        bayer[pixel] = rgb[pixel * 3];
      }
      // store blue
      else if (row % 2 == 0 && col % 2 == 1)
      {
        bayer[pixel] = rgb[pixel * 3 + 2];
      }
      // store green
      else // row, col % 2 == 0 or 1
      {
        bayer[pixel] = rgb[pixel * 3 + 1];
      }
    }
  }
}
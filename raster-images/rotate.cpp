#include "rotate.h"

void rotate(
    const std::vector<unsigned char> &input,
    const int width,
    const int height,
    const int num_channels,
    std::vector<unsigned char> &rotated)
{
  rotated.resize(height * width * num_channels);

  int i = 0;
  // last one in every row is the first new one in every column
  for (int row = width - 1; row >= 0; row--)
  {
    for (int col = 0; col < height; col++)
    {
      for (int h = 0; h < num_channels; h++)
      {
        rotated[i++] = input[(col * width + row) * num_channels + h];
      }
    }
  }
}

#include "reflect.h"

void reflect(
    const std::vector<unsigned char> &input,
    const int width,
    const int height,
    const int num_channels,
    std::vector<unsigned char> &reflected)
{
  reflected.resize(width * height * num_channels);

  // loop thru rows
  for (int row = 0; row < height; row++)
  {
    // first in row has index width * row
    for (int col = 0; col < width; col++)
    {
      // consider a pixel as a whole
      for (int h = 0; h < num_channels; h++)
      {
        // new col == last one in this row - col
        // order inside a triplet doesn't change
        reflected[(width * row + col) * num_channels + h] = input[((width * (row + 1) - 1 - col)) * num_channels + h];
      }
    }
  }
}

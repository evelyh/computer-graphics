#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
    const std::string &filename,
    const std::vector<unsigned char> &data,
    const int width,
    const int height,
    const int num_channels)
{
  assert(
      (num_channels == 3 || num_channels == 1) &&
      ".ppm only supports RGB or grayscale images");

  std::ofstream outfile;
  outfile.open(filename, std::ios::trunc);
  if (!outfile.is_open())
    return false;

  if (num_channels == 3)
    outfile << "P3\n";
  else
    outfile << "P2\n";

  outfile << width << " " << height << "\n"
          << "255\n";

  for (auto i = 0; i < data.size(); i++)
  {
    int val = static_cast<int>(data[i]);
    outfile << val << " ";
    if (num_channels == 3)
    {
      if (i % 3 == 2)
      {
        outfile << "\n";
      }
    }
    else
    {
      outfile << "\n";
    }
  }

  outfile.close();
  return true;
}

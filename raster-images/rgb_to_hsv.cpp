#include "rgb_to_hsv.h"
#include <cmath>
#include <algorithm>

using namespace std;

void rgb_to_hsv(
    const double r,
    const double g,
    const double b,
    double &h,
    double &s,
    double &v)
{
  double max_val = max(max(r, g), b);
  double min_val = min(min(r, g), b);
  double delta = max_val - min_val;

  if (delta == 0)
  {
    h = 0;
  }
  else
  {
    if (max_val == r)
    {
      h = 60 * (fmod(((g - b) / delta), 6));
    }
    else if (max_val == g)
    {
      h = 60 * ((b - r) / delta + 2);
    }
    else if (max_val == b)
    {
      h = 60 * ((r - g) / delta + 4);
    }
  }

  if (max_val == 0)
  {
    s = 0;
  }
  else
  {

    s = delta / max_val;
  }

  v = max_val / 255.0;
}

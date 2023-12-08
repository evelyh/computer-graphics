#include "hsv_to_rgb.h"
#include <cmath>
#include <algorithm>

using namespace std;

void hsv_to_rgb(
    const double h,
    const double s,
    const double v,
    double &r,
    double &g,
    double &b)
{

  double c = v * s;
  double x = c * (1 - fabs(fmod((h / 60.0), 2) - 1));
  double m = v - c;
  double rr, gg, bb;
  if (0 <= h && h < 60)
  {
    rr = c;
    gg = x;
    bb = 0;
  }
  else if (60 <= h && h < 120)
  {
    rr = x;
    gg = c;
    bb = 0;
  }
  else if (120 <= h && h < 180)
  {
    rr = 0;
    gg = c;
    bb = x;
  }
  else if (180 <= h && h < 240)
  {
    rr = 0;
    gg = x;
    bb = c;
  }
  else if (240 <= h && h < 300)
  {
    rr = x;
    gg = 0;
    bb = c;
  }
  else if (300 <= h && h < 360)
  {
    rr = c;
    gg = 0;
    bb = x;
  }
  r = (rr + m) * 255.0;
  g = (gg + m) * 255.0;
  b = (bb + m) * 255.0;
}

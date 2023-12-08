#include "over.h"

void over(
    const std::vector<unsigned char> &A,
    const std::vector<unsigned char> &B,
    const int &width,
    const int &height,
    std::vector<unsigned char> &C)
{
  C.resize(A.size());

  for (int i = 0; i < A.size(); i += 4)
  {
    double alpha_a = A[i + 3] / 255.0;
    double alpha_b = B[i + 3] / 255.0;
    // new alpha value
    C[i + 3] = alpha_a + alpha_b * (1 - alpha_a);

    // new rgb value
    for (int h = 0; h < 3; h++)
    {
      C[i + h] = (A[i + h] * alpha_a + B[i + h] * alpha_b * (1 - alpha_a)) / C[i + 3];
    }

    C[i + 3] *= 255.0;
  }
}

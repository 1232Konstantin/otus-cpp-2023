#include "matrix.h"

#include <iostream>

int main()
{
  Matrix<int, -1, 2> mat;

  for (int i = 0; i < 10; ++i)
  {
    mat[i][i] = i;
    mat[i][9 - i] = 9 - i;
  }

  for (int i = 1; i < 9; ++i)
  {
    for (int j = 1; j < 9; ++j)
    {
      std::cout << mat[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  std::cout << "Size = " << mat.size() << std::endl;
  std::cout << std::endl;

  for (const auto& c : mat)
  {
    int x, y, v;
    std::tie(x, y, v) = c;
    std::cout << "X = " << x << " Y = " << y << " V = " << v << '\n';
  }
  std::cout << std::endl;

  return 0;
}

#if 0

#include "matrix.h"

#include <iostream>

int main()
{
  Matrix<int, 0> mat;

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
#endif

#include <array>
#include <map>
#include <tuple>
#include <memory>

using KeyT = std::array<size_t, 3>;
using StorageT = std::map<KeyT, int>;
using StorageItT = typename StorageT::iterator;

template <size_t OriginalDepth, size_t CurrentDepth>
class Level
{
public:
  static constexpr bool isBottom = false;

  KeyT Key;
  std::shared_ptr<StorageT> Storage;
  
  Level(const int& inIndex, KeyT&& inKey, std::shared_ptr<StorageT> inStorage)
    : Key(std::move(inKey))
    , Storage(std::move(inStorage))
  {
    Key[OriginalDepth - CurrentDepth] = inIndex;
  }

  Level<OriginalDepth, CurrentDepth - 1>& operator[](const int& index)
  {
    return Level<OriginalDepth, CurrentDepth - 1>(index, std::move(Key), Storage);
  }
};

template <size_t OriginalDepth>
class Level<OriginalDepth, 2>
{
public:
  static constexpr bool isBottom = true;

  KeyT Key;
  std::shared_ptr<StorageT> Storage;

  Level(const int& inIndex, KeyT&& inKey, std::shared_ptr<StorageT> inStorage)
    : Key(std::move(inKey))
    , Storage(std::move(inStorage))
  {
    Key[OriginalDepth - 2] = inIndex;
  }

  int& operator[](const int& index)
  {
    Key[OriginalDepth - 1] = index;
    return Storage->operator[](Key);
  }
};

class Mat
{
public:

  std::shared_ptr<StorageT> Storage;

  Mat()
  {
    Storage = std::make_shared<StorageT>();
    Storage->insert({ KeyT{ 0,1,2 }, 42 });
  }

  Level<3, 3>& operator[](const int& index)
  {
    return Level<3, 3>(index, {}, Storage);
  }
};


int main()
{
  Mat m;

  //auto& l1 = m[11];
  //auto& l2 = m[11][22];
  auto& l3 = m[11][22][33];

  m[11][22][33] = 42;

  return 0;
}
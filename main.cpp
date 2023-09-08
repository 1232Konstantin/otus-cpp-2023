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

template <size_t Depth>
class Level
{
public:
    static constexpr bool val = true;
    Level<Depth - 1> get()
    {
        return Level<Depth - 1>();
    }
};

template <>
class Level<1>
{
public:
    static constexpr bool val = false;
};


int main()
{
    Level<3> l3;
    auto vl3 = l3.val;
    auto l2 = l3.get();
    auto vl2 = l2.val;
    auto l1 = l2.get();
    auto vl1 = l1.val;

    return 0;
}
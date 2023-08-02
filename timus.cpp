#include "timus.h"

#include <iostream>

namespace Timus
{
  void task1409(std::istream& in, std::ostream& out)
  {
    int harry, larry;
    in >> harry >> larry;
    out << larry - 1 << ' ' << harry - 1;
  }

  void task1877(std::istream& in, std::ostream& out)
  {
    int lock1, lock2;
    in >> lock1 >> lock2;
    out << ((lock1 == 0 || lock1 % 2 == 0 || lock2 % 2 != 0) ? "yes" : "no");
  }

  void task2001(std::istream& in, std::ostream& out)
  {
    int a1, b1, a2, b2, a3, b3;
    in >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;
    out << a1 - a3 << ' ' << b1 - b2;
  }

  void task1264(std::istream& in, std::ostream& out)
  {
    int n, m;
    in >> n >> m;
    out << n * (m + 1);
  }

  void task1787(std::istream& in, std::ostream& out)
  {
    int k, n;
    in >> k >> n;
    int total = 0;
    for (int i = 0; i < n; ++i)
    {
      int temp;
      in >> temp;
      total += temp;
      total -= k;
      if (total < 0) total = 0;
    }
    out << total;
  }
}
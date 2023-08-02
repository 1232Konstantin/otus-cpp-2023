
#include <gtest/gtest.h>

#include "timus.h"

#include <sstream>
#include <string>
#include <vector>

void TestTask1409(int harry, int larry, int expected_harry, int expected_larry)
{
  std::stringstream input;
  std::stringstream output;

  input << harry << ' ' << larry;

  Timus::task1409(input, output);

  int return_harry, return_larry;
  output >> return_harry >> return_larry;

  EXPECT_EQ(return_harry, expected_harry);
  EXPECT_EQ(return_larry, expected_larry);
}

TEST(Task1409, DefaultTest)
{
  TestTask1409(4, 7, 6, 3);
}

TEST(Task1409, TestOnlyShot)
{
  TestTask1409(1, 5, 4, 0);
}

TEST(Task1409, TestEqualShot)
{
  TestTask1409(5, 5, 4, 4);
}

void TestTask1877(const std::string& lock1, const std::string& lock2, bool expected)
{
  std::stringstream input;
  std::stringstream output;

  input << lock1 << '\n' << lock2;

  Timus::task1877(input, output);

  std::string result;
  output >> result;

  EXPECT_EQ(result, (expected ? "yes" : "no"));
}

TEST(Task1877, DefaultTest1)
{
  TestTask1877("0001", "0000", false);
}

TEST(Task1877, DefaultTest2)
{
  TestTask1877("0002", "0001", true);
}

void TestTask2001(int a1, int b1, int a2, int b2, int a3, int b3, int ex_a, int ex_b)
{
  std::stringstream input;
  std::stringstream output;

  input << a1 << ' ' << b1 << '\n' << a2 << ' ' << b2 << '\n' << a3 << ' ' << b3 << '\n';

  Timus::task2001(input, output);

  int a, b;
  output >> a >> b;

  EXPECT_EQ(a, ex_a);
  EXPECT_EQ(b, ex_b);
}

TEST(Task2001, DefaultTest)
{
  TestTask2001(1, 2, 2, 1, 0, 3, 1, 1);
}

void TestTask1264(int n, int m, int ex)
{
  std::stringstream input;
  std::stringstream output;

  input << n << ' ' << m;

  Timus::task1264(input, output);

  int r;
  output >> r;

  EXPECT_EQ(r, ex);
}

TEST(Task1264, DefaultTest)
{
  TestTask1264(3, 1, 6);
}

void TestTask1787(int k, int n, const std::vector<int>& as, int ex)
{
  std::stringstream input;
  std::stringstream output;

  input << k << ' ' << n << '\n';
  for (int a : as)
  {
    input << a << ' ';
  }

  Timus::task1787(input, output);

  int r;
  output >> r;

  EXPECT_EQ(r, ex);
}

TEST(Task1787, DefaultTest)
{
  TestTask1787(5, 3, {6, 7, 2}, 0);
}

TEST(Task1787, DefaultTest2)
{
  TestTask1787(5, 3, { 20, 0, 0 }, 5);
}
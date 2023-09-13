#include <gtest/gtest.h>

#include "matrix.h"

TEST(MatrixProj, EmptyMatrix) {
	Matrix<int, -1, 2> mat;
	EXPECT_EQ(mat.size(), 0);
}

TEST(MatrixProj, GetDefaultValue) {
	Matrix<int, -1, 2> mat;
	int val = mat[0][0];
	EXPECT_EQ(val, -1);
	EXPECT_EQ(mat.size(), 0);
}

TEST(MatrixProj, SetValue) {
	Matrix<int, -1, 2> mat;
	mat[100][100] = 314;
	EXPECT_EQ(static_cast<int>(mat[100][100]), 314);
	EXPECT_EQ(mat.size(), 1);
}

TEST(MatrixProj, UnSetValue) {
	Matrix<int, -1, 2> mat;
	mat[100][100] = 314;
	EXPECT_EQ(static_cast<int>(mat[100][100]), 314);
	EXPECT_EQ(mat.size(), 1);
	mat[100][100] = -1;
	EXPECT_EQ(mat.size(), 0);
}

TEST(MatrixProj, LoopMatrix) {
	Matrix<int, -1, 2> mat;
	mat[100][100] = 314;

	for (const auto& c : mat)
	{
		int x;
		int y;
		int v;
		std::tie(x, y, v) = c;
		EXPECT_EQ(x, 100);
		EXPECT_EQ(y, 100);
		EXPECT_EQ(v, 314);
	}
}

TEST(MatrixProj, DiagValue) {
	Matrix<int, 0, 2> mat;
	for (int i = 0; i < 10; ++i)
	{
		mat[i][i] = i;
	}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (i == j)
			{
				EXPECT_EQ(static_cast<int>(mat[i][j]), i);
			}
			else
			{
				EXPECT_EQ(static_cast<int>(mat[i][j]), 0);
			}
		}
	}

	EXPECT_EQ(mat.size(), 9);
}

TEST(MatrixProj, Diag2Value) {
	Matrix<int, 0, 2> mat;
	for (int i = 0; i < 10; ++i)
	{
		mat[i][9 - i] = 9 - i;
	}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (i == 9 - j)
			{
				EXPECT_EQ(static_cast<int>(mat[i][j]), 9 - i);
			}
			else
			{
				EXPECT_EQ(static_cast<int>(mat[i][j]), 0);
			}
		}
	}

	EXPECT_EQ(mat.size(), 9);
}

TEST(MatrixProj, NDimention) {
	Matrix<int, -1, 3> mat;
	mat[1][2][3] = 42;
	EXPECT_EQ(static_cast<int>(mat[1][2][3]), 42);
	EXPECT_EQ(mat.size(), 1);
}

TEST(MatrixProj, Canon) {
	Matrix<int, -1, 2> mat;

	((mat[100][100] = 314) = 0) = 217;

	EXPECT_EQ(static_cast<int>(mat[100][100]), 217);
	EXPECT_EQ(mat.size(), 1);
}
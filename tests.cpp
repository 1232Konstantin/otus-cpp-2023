
#include <gtest/gtest.h>

#include "lib.h"

TEST(CMakeProj, VersionIsGreaterThanZero) {
	EXPECT_GT(version(), 0);
}
#include <gtest/gtest.h>

#include "Math.hpp"

TEST(MathTest, ToRadians)
{
  EXPECT_EQ(toRadians(0), 0);
  EXPECT_NEAR(toRadians(180), PI, 0.0001f);
  EXPECT_NEAR(toRadians(90), HALF_PI, 0.0001f);
}
#include <gtest/gtest.h>

#include "Math.hpp"

TEST(MathTest, ToRadians) {
  EXPECT_EQ(toRadians(0), 0);
  EXPECT_NEAR(toRadians(180), PI, 0.0001);
  EXPECT_NEAR(toRadians(90), HALF_PI, 0.0001);
}

TEST(MathTest, ToTangentSpace) {
  const Vector3t normal{0, 0, 1};
  const Vector3t tangent{0, 1, 0};
  const Vector3t bitangent{1, 0, 0};

  const Vector3t test{0, 1, 0};
  const auto result = transformToTangentSpace(test, normal, tangent, bitangent);

  EXPECT_EQ(result, Vector3t(0, 0, 1));
}

TEST(MathTest, FromTangentSpace) {
  const Float v = std::sqrt(2) * 0.5;
  const Vector3t normal{v, v, 0};
  const Vector3t tangent{-v, v, 0};
  const Vector3t bitangent{0, 0, 1};

  const Vector3t test{v, v, 0};
  const auto result = transformFromTangentSpace(test, normal, tangent, bitangent);

  EXPECT_NEAR(result.x, 0, 0.0001);
  EXPECT_NEAR(result.y, 1.0f, 0.0001);
  EXPECT_NEAR(result.z, 0, 0.0001);
}
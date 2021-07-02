#include <gtest/gtest.h>

#include "Math.hpp"
#include "Vector.hpp"

TEST(MathTest, ToRadians) {
  EXPECT_EQ(toRadians(0), 0);
  EXPECT_NEAR(toRadians(180), PI, 0.0001f);
  EXPECT_NEAR(toRadians(90), HALF_PI, 0.0001f);
}

TEST(MathTest, ToTangentSpace) {
  const Vector normal{0, 0, 1};
  const Vector tangent{0, 1, 0};
  const Vector bitangent{1, 0, 0};

  const Vector test{0, 1, 0};
  const auto result = transformToTangentSpace(test, normal, tangent, bitangent);

  EXPECT_EQ(result, Vector(0, 0, 1));
}

TEST(MathTest, FromTangentSpace) {
  const float v = std::sqrt(2) * 0.5f;
  const Vector normal{v, v, 0};
  const Vector tangent{-v, v, 0};
  const Vector bitangent{0, 0, 1};

  const Vector test{v, v, 0};
  const auto result = transformFromTangentSpace(test, normal, tangent, bitangent);

  EXPECT_NEAR(result.x, 0, 0.0001f);
  EXPECT_NEAR(result.y, 1.0f, 0.0001f);
  EXPECT_NEAR(result.z, 0, 0.0001f);
}
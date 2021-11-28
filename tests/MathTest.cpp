#include <gtest/gtest.h>

#include "Math.hpp"
#include "Vector3.hpp"

TEST(MathTest, ToRadians) {
  EXPECT_EQ(toRadians(0), 0);
  EXPECT_NEAR(toRadians(180), PI, 0.0001f);
  EXPECT_NEAR(toRadians(90), HALF_PI, 0.0001f);
}

TEST(MathTest, ToTangentSpace) {
  const Vector3f normal{0, 0, 1};
  const Vector3f tangent{0, 1, 0};
  const Vector3f bitangent{1, 0, 0};

  const Vector3f test{0, 1, 0};
  const auto result = transformToTangentSpace(test, normal, tangent, bitangent);

  EXPECT_EQ(result, Vector3f(0, 0, 1));
}

TEST(MathTest, FromTangentSpace) {
  const float v = std::sqrt(2) * 0.5f;
  const Vector3f normal{v, v, 0};
  const Vector3f tangent{-v, v, 0};
  const Vector3f bitangent{0, 0, 1};

  const Vector3f test{v, v, 0};
  const auto result = transformFromTangentSpace(test, normal, tangent, bitangent);

  EXPECT_NEAR(result.x, 0, 0.0001f);
  EXPECT_NEAR(result.y, 1.0f, 0.0001f);
  EXPECT_NEAR(result.z, 0, 0.0001f);
}
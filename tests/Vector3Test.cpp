#include <gtest/gtest.h>

#include "Types.hpp"

TEST(Vector3Test, Constructors) {
  const Vector3t a{};
  const Vector3t b{1, 4, 2};
  const Vector3t c{42};

  EXPECT_EQ(a.x, 0.0);
  EXPECT_EQ(a.y, 0.0);
  EXPECT_EQ(a.z, 0.0);

  EXPECT_EQ(b.x, 1.0);
  EXPECT_EQ(b.y, 4.0);
  EXPECT_EQ(b.z, 2.0);

  EXPECT_EQ(c.x, 42.0);
  EXPECT_EQ(c.y, 42.0);
  EXPECT_EQ(c.z, 42.0);
}

TEST(Vector3Test, Comparison) {
  const Vector3t a{1, 2, 3};
  const Vector3t b{2, 2, 3};
  const Vector3t c{1, 3, 3};
  const Vector3t d{1, 2, 4};
  const Vector3t e{1, 2, 3};

  EXPECT_TRUE(a == e);
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_TRUE(a != d);
}

TEST(Vector3Test, Length) {
  const Vector3t a{2, 3, 6};
  EXPECT_EQ(a.length(), 7);
}

TEST(Vector3Test, LengthSquared) {
  const Vector3t a{2, 3, 6};
  EXPECT_EQ(a.lengthSq(), 49);
}

TEST(Vector3Test, Normalization) {
  const Vector3t a{};
  const Vector3t b{2, 3, 6};
  const Vector3t aNormalized = a.normalized();
  const Vector3t bNormalized = b.normalized();

  EXPECT_EQ(aNormalized.lengthSq(), 0.0);
  EXPECT_EQ(aNormalized.x, 0.0);
  EXPECT_EQ(aNormalized.y, 0.0);
  EXPECT_EQ(aNormalized.z, 0.0);

  EXPECT_NEAR(bNormalized.lengthSq(), 1.0, 0.0001);
  EXPECT_NEAR(bNormalized.x, 2.0 / 7.0, 0.0001);
  EXPECT_NEAR(bNormalized.y, 3.0 / 7.0, 0.0001);
  EXPECT_NEAR(bNormalized.z, 6.0 / 7.0, 0.0001);
}

TEST(Vector3Test, Clamp) {
  const Vector3t a{-0.5, 0.5, 2.0};
  const Vector3t b{0.5, -0.5, 2.0};
  const Vector3t c{2.0, -0.5, 0.5};

  const Vector3t expectedA{0.0, 0.5, 1.0};
  const Vector3t expectedB{0.5, 0.0, 1.0};
  const Vector3t expectedC{1.0, 0.0, 0.5};

  EXPECT_EQ(a.clamped(), expectedA);
  EXPECT_EQ(b.clamped(), expectedB);
  EXPECT_EQ(c.clamped(), expectedC);
}

TEST(Vector3Test, DotProduct) {
  const Vector3t a{4, 2, 1};
  const Vector3t b{2, 3, 6};

  EXPECT_EQ(a.dot(b), 20);
}

TEST(Vector3Test, CrossProduct) {
  const Vector3t a{4, 2, 1};
  const Vector3t b{2, 3, 6};

  const Vector3t expected{9, -22, 8};

  EXPECT_EQ(a.cross(b), expected);
}

TEST(Vector3Test, UnaryMinus) {
  const Vector3t a{4, 2, 1};
  const Vector3t b = -a;

  EXPECT_EQ(b.x, -4);
  EXPECT_EQ(b.y, -2);
  EXPECT_EQ(b.z, -1);
}

TEST(Vector3Test, Addition) {
  Vector3t a{4, 2, 1};
  const Vector3t b{2, 3, 6};

  const Vector3t expected{6, 5, 7};

  EXPECT_EQ(a + b, expected);

  a += b;
  EXPECT_EQ(a, expected);
}

TEST(Vector3Test, Subtraction) {
  Vector3t a{4, 2, 1};
  const Vector3t b{2, 3, 6};

  const Vector3t expected{2, -1, -5};

  EXPECT_EQ(a - b, expected);

  a -= b;
  EXPECT_EQ(a, expected);
}

TEST(Vector3Test, ScalarMultiplication) {
  Vector3t a{4, 2, 1};
  const Float r = 2.0f;

  const Vector3t expected{8, 4, 2};

  EXPECT_EQ(a * r, expected);
  EXPECT_EQ(r * a, expected);

  a *= r;
  EXPECT_EQ(a, expected);
}

TEST(Vector3Test, Multiplication) {
  Vector3t a{4, 2, 1};
  Vector3t b{2, 1, 3};

  const Vector3t expected{8, 2, 3};

  EXPECT_EQ(a * b, expected);

  a *= b;
  EXPECT_EQ(a, expected);
}

TEST(Vector3Test, Division) {
  Vector3t a{4, 2, 1};
  const Float r = 2.0f;

  const Vector3t expected{2, 1, 0.5};

  EXPECT_EQ(a / r, expected);

  a /= r;
  EXPECT_EQ(a, expected);
}
#include <gtest/gtest.h>

#include "Vector3.hpp"

TEST(Vector3Test, Constructors) {
  const Vector3f a{};
  const Vector3f b{1, 4, 2};
  const Vector3f c{42};

  EXPECT_EQ(a.x, 0.0f);
  EXPECT_EQ(a.y, 0.0f);
  EXPECT_EQ(a.z, 0.0f);

  EXPECT_EQ(b.x, 1.0f);
  EXPECT_EQ(b.y, 4.0f);
  EXPECT_EQ(b.z, 2.0f);

  EXPECT_EQ(c.x, 42.0f);
  EXPECT_EQ(c.y, 42.0f);
  EXPECT_EQ(c.z, 42.0f);
}

TEST(Vector3Test, Comparison) {
  const Vector3f a{1, 2, 3};
  const Vector3f b{2, 2, 3};
  const Vector3f c{1, 3, 3};
  const Vector3f d{1, 2, 4};
  const Vector3f e{1, 2, 3};

  EXPECT_TRUE(a == e);
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_TRUE(a != d);
}

TEST(Vector3Test, Length) {
  const Vector3f a{2, 3, 6};
  EXPECT_EQ(a.length(), 7);
}

TEST(Vector3Test, LengthSquared) {
  const Vector3f a{2, 3, 6};
  EXPECT_EQ(a.lengthSq(), 49);
}

TEST(Vector3Test, Normalization) {
  const Vector3f a{};
  const Vector3f b{2, 3, 6};
  const Vector3f aNormalized = a.normalized();
  const Vector3f bNormalized = b.normalized();

  EXPECT_EQ(aNormalized.lengthSq(), 0.0f);
  EXPECT_EQ(aNormalized.x, 0.0f);
  EXPECT_EQ(aNormalized.y, 0.0f);
  EXPECT_EQ(aNormalized.z, 0.0f);

  EXPECT_NEAR(bNormalized.lengthSq(), 1.0f, 0.0001f);
  EXPECT_NEAR(bNormalized.x, 2.0f / 7.0f, 0.0001f);
  EXPECT_NEAR(bNormalized.y, 3.0f / 7.0f, 0.0001f);
  EXPECT_NEAR(bNormalized.z, 6.0f / 7.0f, 0.0001f);
}

TEST(Vector3Test, Clamp) {
  const Vector3f a{-0.5f, 0.5f, 2.0f};
  const Vector3f b{0.5f, -0.5f, 2.0f};
  const Vector3f c{2.0f, -0.5f, 0.5f};

  const Vector3f expectedA{0.0f, 0.5f, 1.0f};
  const Vector3f expectedB{0.5f, 0.0f, 1.0f};
  const Vector3f expectedC{1.0f, 0.0f, 0.5f};

  EXPECT_EQ(a.clamped(), expectedA);
  EXPECT_EQ(b.clamped(), expectedB);
  EXPECT_EQ(c.clamped(), expectedC);
}

TEST(Vector3Test, DotProduct) {
  const Vector3f a{4, 2, 1};
  const Vector3f b{2, 3, 6};

  EXPECT_EQ(a.dot(b), 20);
}

TEST(Vector3Test, CrossProduct) {
  const Vector3f a{4, 2, 1};
  const Vector3f b{2, 3, 6};

  const Vector3f expected{9, -22, 8};

  EXPECT_EQ(a.cross(b), expected);
}

TEST(Vector3Test, UnaryMinus) {
  const Vector3f a{4, 2, 1};
  const Vector3f b = -a;

  EXPECT_EQ(b.x, -4);
  EXPECT_EQ(b.y, -2);
  EXPECT_EQ(b.z, -1);
}

TEST(Vector3Test, Addition) {
  Vector3f a{4, 2, 1};
  const Vector3f b{2, 3, 6};

  const Vector3f expected{6, 5, 7};

  EXPECT_EQ(a + b, expected);

  a += b;
  EXPECT_EQ(a, expected);
}

TEST(Vector3Test, Subtraction) {
  Vector3f a{4, 2, 1};
  const Vector3f b{2, 3, 6};

  const Vector3f expected{2, -1, -5};

  EXPECT_EQ(a - b, expected);

  a -= b;
  EXPECT_EQ(a, expected);
}

TEST(Vector3Test, ScalarMultiplication) {
  Vector3f a{4, 2, 1};
  const float r = 2.0f;

  const Vector3f expected{8, 4, 2};

  EXPECT_EQ(a * r, expected);
  EXPECT_EQ(r * a, expected);

  a *= r;
  EXPECT_EQ(a, expected);
}

TEST(Vector3Test, Multiplication) {
  Vector3f a{4, 2, 1};
  Vector3f b{2, 1, 3};

  const Vector3f expected{8, 2, 3};

  EXPECT_EQ(a * b, expected);

  a *= b;
  EXPECT_EQ(a, expected);
}

TEST(Vector3Test, Division) {
  Vector3f a{4, 2, 1};
  const float r = 2.0f;

  const Vector3f expected{2, 1, 0.5f};

  EXPECT_EQ(a / r, expected);

  a /= r;
  EXPECT_EQ(a, expected);
}
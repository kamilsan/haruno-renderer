#include <gtest/gtest.h>

#include "Vector4.hpp"

TEST(Vector4Test, Constructors) {
  const Vector4f a{};
  const Vector4f b{1, 4, 2, 8};
  const Vector4f c{42};
  const Vector4f d{Vector3f{4, 2, 3}, 1};

  EXPECT_EQ(a.x, 0.0f);
  EXPECT_EQ(a.y, 0.0f);
  EXPECT_EQ(a.z, 0.0f);
  EXPECT_EQ(a.w, 0.0f);

  EXPECT_EQ(b.x, 1.0f);
  EXPECT_EQ(b.y, 4.0f);
  EXPECT_EQ(b.z, 2.0f);
  EXPECT_EQ(b.w, 8.0f);

  EXPECT_EQ(c.x, 42.0f);
  EXPECT_EQ(c.y, 42.0f);
  EXPECT_EQ(c.z, 42.0f);
  EXPECT_EQ(c.w, 42.0f);

  EXPECT_EQ(d.x, 4.0f);
  EXPECT_EQ(d.y, 2.0f);
  EXPECT_EQ(d.z, 3.0f);
  EXPECT_EQ(d.w, 1.0f);
}

TEST(Vector4Test, Comparison) {
  const Vector4f a{1, 2, 3, 4};
  const Vector4f b{2, 2, 3, 4};
  const Vector4f c{1, 3, 3, 4};
  const Vector4f d{1, 2, 4, 4};
  const Vector4f e{1, 2, 3, 5};
  const Vector4f f{1, 2, 3, 4};

  EXPECT_TRUE(a == f);
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_TRUE(a != d);
  EXPECT_TRUE(a != e);
}

TEST(Vector4Test, Length) {
  const Vector4f a{2, 3, 6, 0};
  const Vector4f b{2, 3, 0, 6};
  EXPECT_EQ(a.length(), 7);
  EXPECT_EQ(b.length(), 7);
}

TEST(Vector4Test, LengthSquared) {
  const Vector4f a{2, 3, 6, 0};
  const Vector4f b{2, 3, 0, 6};
  EXPECT_EQ(a.lengthSq(), 49);
  EXPECT_EQ(b.lengthSq(), 49);
}

TEST(Vector4Test, Normalization) {
  const Vector4f a{};
  const Vector4f b{2, 3, 6, 1};
  const Vector4f aNormalized = a.normalized();
  const Vector4f bNormalized = b.normalized();

  EXPECT_EQ(aNormalized.lengthSq(), 0.0f);
  EXPECT_EQ(aNormalized.x, 0.0f);
  EXPECT_EQ(aNormalized.y, 0.0f);
  EXPECT_EQ(aNormalized.z, 0.0f);
  EXPECT_EQ(aNormalized.w, 0.0f);

  const float scale = std::sqrt(50.0f);
  EXPECT_NEAR(bNormalized.lengthSq(), 1.0f, 0.0001f);
  EXPECT_NEAR(bNormalized.x, 2.0f / scale, 0.0001f);
  EXPECT_NEAR(bNormalized.y, 3.0f / scale, 0.0001f);
  EXPECT_NEAR(bNormalized.z, 6.0f / scale, 0.0001f);
  EXPECT_NEAR(bNormalized.z, 6.0f / scale, 0.0001f);
  EXPECT_NEAR(bNormalized.w, 1.0f / scale, 0.0001f);
}

TEST(Vector4Test, Clamp) {
  const Vector4f a{-0.5f, 0.5f, 2.0f, 0.5f};
  const Vector4f b{0.5f, -0.5f, 2.0f, 0.2f};
  const Vector4f c{2.0f, -0.5f, 0.5f, 0.1f};
  const Vector4f d{2.0f, -0.5f, 0.5f, -0.1f};

  const Vector4f expectedA{0.0f, 0.5f, 1.0f, 0.5f};
  const Vector4f expectedB{0.5f, 0.0f, 1.0f, 0.2f};
  const Vector4f expectedC{
      1.0f,
      0.0f,
      0.5f,
      0.1f,
  };
  const Vector4f expectedD{1.0f, 0.0f, 0.5f, 0.0f};

  EXPECT_EQ(a.clamped(), expectedA);
  EXPECT_EQ(b.clamped(), expectedB);
  EXPECT_EQ(c.clamped(), expectedC);
  EXPECT_EQ(d.clamped(), expectedD);
}

TEST(Vector4Test, DotProduct) {
  const Vector4f a{4, 2, 1, 5};
  const Vector4f b{2, 3, 6, 3};

  EXPECT_EQ(a.dot(b), 35);
}

TEST(Vector4Test, UnaryMinus) {
  const Vector4f a{4, 2, 1, 3};
  const Vector4f b = -a;

  EXPECT_EQ(b.x, -4);
  EXPECT_EQ(b.y, -2);
  EXPECT_EQ(b.z, -1);
  EXPECT_EQ(b.w, -3);
}

TEST(Vector4Test, Addition) {
  Vector4f a{4, 2, 1, 3};
  const Vector4f b{2, 3, 6, 1};

  const Vector4f expected{6, 5, 7, 4};

  EXPECT_EQ(a + b, expected);

  a += b;
  EXPECT_EQ(a, expected);
}

TEST(Vector4Test, Subtraction) {
  Vector4f a{4, 2, 1, 10};
  const Vector4f b{2, 3, 6, 4};

  const Vector4f expected{2, -1, -5, 6};

  EXPECT_EQ(a - b, expected);

  a -= b;
  EXPECT_EQ(a, expected);
}

TEST(Vector4Test, ScalarMultiplication) {
  Vector4f a{4, 2, 1, 3};
  const float r = 2.0f;

  const Vector4f expected{8, 4, 2, 6};

  EXPECT_EQ(a * r, expected);
  EXPECT_EQ(r * a, expected);

  a *= r;
  EXPECT_EQ(a, expected);
}

TEST(Vector4Test, Multiplication) {
  Vector4f a{4, 2, 1, 5};
  Vector4f b{2, 1, 3, 2};

  const Vector4f expected{8, 2, 3, 10};

  EXPECT_EQ(a * b, expected);

  a *= b;
  EXPECT_EQ(a, expected);
}

TEST(Vector4Test, Division) {
  Vector4f a{4, 2, 1, 8};
  const float r = 2.0f;

  const Vector4f expected{2, 1, 0.5f, 4};

  EXPECT_EQ(a / r, expected);

  a /= r;
  EXPECT_EQ(a, expected);
}
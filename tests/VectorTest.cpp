#include <gtest/gtest.h>

#include "Vector.hpp"

TEST(VectorTest, Constructors)
{
  const Vector a{};
  const Vector b{1, 4, 2};

  EXPECT_EQ(a.x, 0.0f);
  EXPECT_EQ(a.y, 0.0f);
  EXPECT_EQ(a.z, 0.0f);

  EXPECT_EQ(b.x, 1.0f);
  EXPECT_EQ(b.y, 4.0f);
  EXPECT_EQ(b.z, 2.0f);
}

TEST(VectorTest, Comparison)
{
  const Vector a{1, 2, 3};
  const Vector b{2, 2, 3};
  const Vector c{1, 3, 3};
  const Vector d{1, 2, 4};
  const Vector e{1, 2, 3};

  EXPECT_TRUE(a == e);
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_TRUE(a != d);
}

TEST(VectorTest, Length)
{
  const Vector a{2, 3, 6};
  EXPECT_EQ(a.length(), 7);
}

TEST(VectorTest, LengthSquared)
{
  const Vector a{2, 3, 6};
  EXPECT_EQ(a.lengthSq(), 49);
}

TEST(VectorTest, Normalization)
{
  const Vector a{};
  const Vector b{2, 3, 6};
  const Vector aNormalized = a.normalized();
  const Vector bNormalized = b.normalized();


  EXPECT_EQ(aNormalized.lengthSq(), 0.0f);
  EXPECT_EQ(aNormalized.x, 0.0f);
  EXPECT_EQ(aNormalized.y, 0.0f);
  EXPECT_EQ(aNormalized.z, 0.0f);

  EXPECT_NEAR(bNormalized.lengthSq(), 1.0f, 0.0001f);
  EXPECT_NEAR(bNormalized.x, 2.0f/7.0f, 0.0001f);
  EXPECT_NEAR(bNormalized.y, 3.0f/7.0f, 0.0001f);
  EXPECT_NEAR(bNormalized.z, 6.0f/7.0f, 0.0001f);
}

TEST(VectorTest, Clamp)
{
  const Vector a{-0.5f, 0.5f, 2.0f};
  const Vector b{0.5f, -0.5f, 2.0f};
  const Vector c{2.0f, -0.5f, 0.5f};
  
  const Vector expectedA{0.0f, 0.5f, 1.0f};
  const Vector expectedB{0.5f, 0.0f, 1.0f};
  const Vector expectedC{1.0f, 0.0f, 0.5f};

  EXPECT_EQ(a.clamped(), expectedA);
  EXPECT_EQ(b.clamped(), expectedB);
  EXPECT_EQ(c.clamped(), expectedC);
}

TEST(VectorTest, DotProduct)
{
  const Vector a{4, 2, 1};
  const Vector b{2, 3, 6};

  EXPECT_EQ(a.dot(b), 20);
}

TEST(VectorTest, CrossProduct)
{
  const Vector a{4, 2, 1};
  const Vector b{2, 3, 6};

  const Vector expected{9, -22, 8};
  
  EXPECT_EQ(a.cross(b), expected);
}

TEST(VectorTest, UnaryMinus)
{
  const Vector a{4, 2, 1};
  const Vector b = -a;

  EXPECT_EQ(b.x, -4);
  EXPECT_EQ(b.y, -2);
  EXPECT_EQ(b.z, -1);
}

TEST(VectorTest, Addition)
{
  Vector a{4, 2, 1};
  const Vector b{2, 3, 6};

  const Vector expected{6, 5, 7};

  EXPECT_EQ(a + b, expected);

  a += b;
  EXPECT_EQ(a, expected);
}

TEST(VectorTest, Subtraction)
{
  Vector a{4, 2, 1};
  const Vector b{2, 3, 6};

  const Vector expected{2, -1, -5};

  EXPECT_EQ(a - b, expected);

  a -= b;
  EXPECT_EQ(a, expected);
}

TEST(VectorTest, ScalarMultiplication)
{
  Vector a{4, 2, 1};
  const float r = 2.0f;

  const Vector expected{8, 4, 2};

  EXPECT_EQ(a * r, expected);
  EXPECT_EQ(r * a, expected);

  a *= r;
  EXPECT_EQ(a, expected);
}

TEST(VectorTest, Multiplication)
{
  Vector a{4, 2, 1};
  Vector b{2, 1, 3};

  const Vector expected{8, 2, 3};

  EXPECT_EQ(a * b, expected);

  a *= b;
  EXPECT_EQ(a, expected);
}

TEST(VectorTest, Division)
{
  Vector a{4, 2, 1};
  const float r = 2.0f;

  const Vector expected{2, 1, 0.5f};

  EXPECT_EQ(a / r, expected);

  a /= r;
  EXPECT_EQ(a, expected);
}
#include <gtest/gtest.h>

#include "Matrix4.hpp"

TEST(Matrix4Test, Multiplication) {
  const Matrix4f a({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
  const Matrix4f b({2, -1, 1, 6, 5, 3, 4, -3, -2, -6, 7, -4, 10, 11, 13, 12});

  const Matrix4f expectedResult({
      46,
      31,
      82,
      36,
      106,
      59,
      182,
      80,
      166,
      87,
      282,
      124,
      226,
      115,
      382,
      168,
  });

  const auto result = a * b;

  EXPECT_EQ(result, expectedResult);
}
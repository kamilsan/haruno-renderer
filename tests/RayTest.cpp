#include <gtest/gtest.h>

#include "Ray.hpp"

TEST(RayTest, Constructor)
{
  Ray ray{Vector{1, 2, 3}, Vector{2, 3, 4}};

  EXPECT_EQ(ray.getOrigin(), Vector(1, 2, 3));
  EXPECT_EQ(ray.getDirection(), Vector(2, 3, 4));
}

TEST(RayTest, At)
{
  Ray ray{Vector{1, 2, 3}, Vector{2, 3, 4}};

  const Vector expected{5, 8, 11};
  EXPECT_EQ(ray.at(2), expected); 
}

TEST(RayTest, OperatorAt)
{
  Ray ray{Vector{1, 2, 3}, Vector{2, 3, 4}};

  const Vector expected{5, 8, 11};
  EXPECT_EQ(ray(2), expected); 
}
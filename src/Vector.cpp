#include "Vector.hpp"

Vector Vector::normalized() const
{
  const float len = length();
  if(len > 0.00001f)
  {
    const float f = 1.0f/len;
    return Vector{x * f, y * f, z * f};
  }
  return Vector{};
}

Vector Vector::clamped(float min, float max) const
{
  float newX = x;
  float newY = y;
  float newZ = z;

  if(newX < min) 
    newX = min;
  else if(newX > max) 
    newX = max;
  
  if(newY < min) 
    newY = min;
  else if(newY > max)
    newY = max;
  
  if(newZ < min)
    newZ = min;
  else if(newZ > max)
    newZ = max;

  return Vector{newX, newY, newZ};
}
#ifndef OBJECT_HPP
#define OBJECT_HPP

class Ray;

class Object
{
public:
  virtual float intersects(const Ray& ray) const = 0;
};

#endif
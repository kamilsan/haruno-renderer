#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <array>
#include <cmath>

#include "Vector3.hpp"
#include "Vector4.hpp"

template <typename T>
class Matrix4 {
 private:
  static constexpr size_t N = 4;
  static constexpr size_t L = N * N;

 public:
  Matrix4()
      : data_({1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0}) {}
  explicit Matrix4(const std::array<T, L>& data) : data_(data) {}

  static Matrix4 initTranslation(const Vector3<T>& translation);
  static Matrix4 initScaling(const Vector3<T>& scaling);
  static Matrix4 initRotation(const Vector3<T>& eulerAngles);

  const T& at(size_t i, size_t j) const { return data_[N * i + j]; }
  T& at(size_t i, size_t j) { return data_[N * i + j]; }

  const T& operator[](size_t i) const { return data_[i]; }
  T& operator[](size_t i) { return data_[i]; }

  Matrix4 transpose() const {
    std::array<T, L> newData;

    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        newData[idx(i, j)] = at(j, i);
      }
    }

    return Matrix4(newData);
  }

  bool operator==(const Matrix4& other) const {
    for (size_t i = 0; i < L; ++i) {
      if (data_[i] != other.data_[i]) {
        return false;
      }
    }

    return true;
  }

  bool operator!=(const Matrix4& other) const {
    for (size_t i = 0; i < L; ++i) {
      if (data_[i] != other.data_[i]) {
        return true;
      }
    }

    return false;
  }

  Matrix4 operator+(const Matrix4& other) const {
    std::array<T, L> newData;
    for (size_t i = 0; i < L; ++i) {
      newData[i] = data_[i] + other.data_[i];
    }

    return Matrix4(newData);
  }

  Matrix4 operator-() const {
    std::array<T, L> newData;
    for (size_t i = 0; i < L; ++i) {
      newData[i] = -data_[i];
    }

    return Matrix4(newData);
  }

  Matrix4 operator-(const Matrix4& other) const {
    std::array<T, L> newData;
    for (size_t i = 0; i < L; ++i) {
      newData[i] = data_[i] - other.data_[i];
    }

    return Matrix4(newData);
  }

  Matrix4 operator*(const T value) const {
    std::array<T, L> newData;
    for (size_t i = 0; i < L; ++i) {
      newData[i] = data_[i] * value;
    }

    return Matrix4(newData);
  }

  Vector4<T> operator*(const Vector4<T>& other) const {
    Vector4<T> result;
    for (size_t i = 0; i < N; ++i) {
      T acc = 0;
      for (size_t j = 0; j < N; ++j) {
        acc += at(i, j) * other[j];
      }
      result[i] = acc;
    }

    return result;
  }

  Matrix4 operator*(const Matrix4& other) const {
    std::array<T, L> newData;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        T acc = 0;
        for (size_t r = 0; r < N; ++r) {
          acc += at(i, r) * other.at(r, j);
        }
        newData[idx(i, j)] = acc;
      }
    }

    return Matrix4(newData);
  }

  Matrix4 operator/(const T value) const {
    std::array<T, L> newData;

    const T f = 1.0 / value;
    for (size_t i = 0; i < L; ++i) {
      newData[i] = data_[i] * f;
    }

    return Matrix4(newData);
  }

  Matrix4& operator+=(const Matrix4& other) {
    for (size_t i = 0; i < L; ++i) {
      data_[i] += other.data_[i];
    }

    return *this;
  }

  Matrix4& operator-=(const Matrix4& other) {
    for (size_t i = 0; i < L; ++i) {
      data_[i] -= other.data_[i];
    }

    return *this;
  }

  Matrix4 operator*=(const T value) const {
    for (size_t i = 0; i < L; ++i) {
      data_[i] *= value;
    }

    return *this;
  }

  Matrix4 operator/=(const T value) const {
    const T f = 1.0 / value;
    for (size_t i = 0; i < L; ++i) {
      data_[i] *= f;
    }

    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix4<T>& m) {
    return os << "[" << m.at(0, 0) << ", " << m.at(0, 1) << ", " << m.at(0, 2) << ", " << m.at(0, 3)
              << "]\n"
              << "[" << m.at(1, 0) << ", " << m.at(1, 1) << ", " << m.at(1, 2) << ", " << m.at(1, 3)
              << "]\n"
              << "[" << m.at(2, 0) << ", " << m.at(2, 1) << ", " << m.at(2, 2) << ", " << m.at(2, 3)
              << "]\n"
              << "[" << m.at(3, 0) << ", " << m.at(3, 1) << ", " << m.at(3, 2) << ", " << m.at(3, 3)
              << "]";
  }

 private:
  static inline size_t idx(size_t i, size_t j) { return N * i + j; }

  std::array<T, L> data_;
};

template <typename T>
Matrix4<T> Matrix4<T>::initTranslation(const Vector3<T>& translation) {
  return Matrix4({1.0, 0.0, 0.0, translation.x, 0.0, 1.0, 0.0, translation.y, 0.0, 0.0, 1.0,
                  translation.z, 0.0, 0.0, 0.0, 1.0});
}

template <typename T>
Matrix4<T> Matrix4<T>::initScaling(const Vector3<T>& scaling) {
  return Matrix4({scaling.x, 0.0, 0.0, 0.0, 0.0, scaling.y, 0.0, 0.0, 0.0, 0.0, scaling.z, 0.0, 0.0,
                  0.0, 0.0, 1.0});
}

template <typename T>
Matrix4<T> Matrix4<T>::initRotation(const Vector3<T>& eulerAngles) {
  const T sinX = std::sin(eulerAngles.x);
  const T cosX = std::cos(eulerAngles.x);
  const T sinY = std::sin(eulerAngles.y);
  const T cosY = std::cos(eulerAngles.y);
  const T sinZ = std::sin(eulerAngles.z);
  const T cosZ = std::cos(eulerAngles.z);

  const Matrix4 rx({1, 0, 0, 0, 0, cosX, -sinX, 0, 0, sinX, cosX, 0, 0, 0, 0, 1});
  const Matrix4 ry({cosY, 0, sinY, 0, 0, 1, 0, 0, -sinY, 0, cosY, 0, 0, 0, 0, 1});
  const Matrix4 rz({cosZ, -sinZ, 0, 0, sinZ, cosZ, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});

  return rz * ry * rx;
}

#endif  // MATRIX4_HPP
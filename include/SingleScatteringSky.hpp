#ifndef SINGLE_SCATTERING_SKY_HPP
#define SINGLE_SCATTERING_SKY_HPP

#include "Color.hpp"
#include "Environment.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

class SingleScatteringSky : public Environment {
 public:
  struct SkyParameters {
    size_t scatteringSamples = 128;
    size_t opticalDensitySamples = 16;
    float earthRadius = 6360'000.0f;
    float atmosphereRadius = 6420'000.0f;
    float atmosphereThickness = 7994.0f;
    float atmosphereThicknessAerosols = 1200.0f;
    float mieScatteringG = 0.7f;
    Color beta;
    Color betaAerosols;
    Color sunColor;
  };

  SingleScatteringSky(const SkyParameters& skyParameters, const Vector3f& sunDirection,
                      float observerAltitude)
      : parameters_(skyParameters),
        sunDirection_(sunDirection),
        observerAltitude_(observerAltitude) {}

  SingleScatteringSky(const Vector3f& sunDirection, float observerAltitude)
      : parameters_(getDefaultParameters()),
        sunDirection_(sunDirection),
        observerAltitude_(observerAltitude) {}

  static SkyParameters getDefaultParameters();

  Color getColor(const Vector3f& direction) const override;

  const SkyParameters& getParameters() const { return parameters_; }
  const Vector3f& getSunDirection() const { return sunDirection_; }
  float getObserverAltitude() const { return observerAltitude_; }

  void setParameters(const SkyParameters& parameters) { parameters_ = parameters; }
  void setSunDirection(const Vector3f& sunDirection) { sunDirection_ = sunDirection; }
  void setObserverAltitude(float observerAltitude) { observerAltitude_ = observerAltitude; }

 private:
  SkyParameters parameters_;
  Vector3f sunDirection_;
  float observerAltitude_;

  float getDensityAtPosition(const Vector3f& position) const;
  float getAerosolsDensityAtPosition(const Vector3f& position) const;

  float computeRayleighPhaseFunction(float cosAngle) const;
  float computeMiePhaseFunction(float g, float cosAngle) const;

  Color computeOpticalDepth(const Ray& ray, float maxT) const;
};

#endif
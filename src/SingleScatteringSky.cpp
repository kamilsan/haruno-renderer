#include "SingleScatteringSky.hpp"

#include "Math.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

Color SingleScatteringSky::getColor(const Vector3f& direction) const {
  Color finalColor{0};

  const Vector3f earthCenter(0.0f, 0.0f, 0.0f);
  const Sphere earthSphere(earthCenter, parameters_.earthRadius, nullptr);
  const Sphere atmosphereSphere(earthCenter, parameters_.atmosphereRadius, nullptr);

  const Vector3f observerPosition{0.0f, parameters_.earthRadius + observerAltitude_, 0.0f};
  const Ray viewRay{observerPosition, direction};

  SurfaceInfo surfaceInfo;
  const auto tEarth = earthSphere.intersects(viewRay, surfaceInfo);

  if (tEarth > 0) {
    return Color{0};
  }

  const auto cosAngle = direction.dot(sunDirection_);
  const auto rayleighPhaseFunction = computeRayleighPhaseFunction(cosAngle);
  const auto miePhaseFunction = computeMiePhaseFunction(parameters_.mieScatteringG, cosAngle);

  const auto tAtmosphereEscape = atmosphereSphere.intersects(viewRay, surfaceInfo);
  const auto deltaT = tAtmosphereEscape / parameters_.scatteringSamples;

  Color accumulatedViewSampleOpticalDepth{0.0};
  auto previousSamplePosition = observerPosition;
  float previousT = 0.0f;

  for (size_t sample = 0; sample < parameters_.scatteringSamples; ++sample) {
    const auto currentT = (sample + 0.5f) * deltaT;
    const auto samplePosition = viewRay(currentT);

    const Ray toSunRay{samplePosition, sunDirection_};
    const auto tSampleToSun = atmosphereSphere.intersects(toSunRay, surfaceInfo);
    const auto tEarthFromSample = earthSphere.intersects(toSunRay, surfaceInfo);

    // Light is not occluded by the Earth
    if (tEarthFromSample < 0) {
      const Ray previousToCurrentSampleRay(previousSamplePosition, direction); 
      const auto partialViewSampleOpticalDepth = computeOpticalDepth(previousToCurrentSampleRay, currentT - previousT);
      accumulatedViewSampleOpticalDepth += partialViewSampleOpticalDepth;

      const auto sampleLightOpticalDepth = computeOpticalDepth(toSunRay, tSampleToSun);
      const auto totalPathOpticalDepth = accumulatedViewSampleOpticalDepth + sampleLightOpticalDepth;
      const Color totalTransmittance{std::exp(-totalPathOpticalDepth.r), std::exp(-totalPathOpticalDepth.g), std::exp(-totalPathOpticalDepth.b)}; 

      const auto density = getDensityAtPosition(samplePosition);
      const auto scatteringCoefficient = parameters_.beta * density;

      const auto aerosolsDensity = getAerosolsDensityAtPosition(samplePosition);
      const auto mieScatteringCoefficient = parameters_.betaAerosols * aerosolsDensity;

      const auto LsUnabsorbed = (scatteringCoefficient * rayleighPhaseFunction +
                      mieScatteringCoefficient * miePhaseFunction) * parameters_.sunColor;
      finalColor += totalTransmittance * LsUnabsorbed * deltaT;
    }

    previousSamplePosition = samplePosition;
    previousT = currentT;
  }

  return finalColor;
}

float SingleScatteringSky::getDensityAtPosition(const Vector3f& position) const {
  const auto h = position.length() - parameters_.earthRadius;
  const auto h0 = parameters_.atmosphereThickness;

  return std::exp(-h / h0);
}

float SingleScatteringSky::getAerosolsDensityAtPosition(const Vector3f& position) const {
  const auto h = position.length() - parameters_.earthRadius;
  const auto h0 = parameters_.atmosphereThicknessAerosols;

  return std::exp(-h / h0);
}

float SingleScatteringSky::computeRayleighPhaseFunction(float cosAngle) const {
  return 3.0f / (16.0f * PI) * (1.0f + cosAngle * cosAngle);
}

float SingleScatteringSky::computeMiePhaseFunction(float g, float cosAngle) const {
  const auto g2 = g * g;
  const auto term1 = (3.0f * (1.0f - g2)) / (8.0f * PI * (2.0f + g2));
  const auto denom = std::pow(1.0f + g2 - 2.0f * g * cosAngle, 1.5f);
  const auto term2 = (1.0f + cosAngle * cosAngle) / denom;

  return term1 * term2;
}

Color SingleScatteringSky::computeOpticalDepth(const Ray& ray, float maxT) const {
  const auto deltaT = maxT / parameters_.opticalDensitySamples;

  float densityIntegral = 0.0f;
  float aerosolsDensityIntegral = 0.0f;

  float t = 0.0f;

  for (size_t sample = 0; sample < parameters_.opticalDensitySamples; ++sample) {
    const auto samplePosition = ray(t + deltaT * 0.5f);
    const auto density = getDensityAtPosition(samplePosition);
    const auto aerosolsDensity = getAerosolsDensityAtPosition(samplePosition);

    densityIntegral += density * deltaT;
    aerosolsDensityIntegral += aerosolsDensity * deltaT;

    t += deltaT;
  }

  const auto opticalDepth = parameters_.beta * densityIntegral;
  const auto mieOpticalDepth = parameters_.betaAerosols * aerosolsDensityIntegral;

  return opticalDepth + mieOpticalDepth;
}

SingleScatteringSky::SkyParameters SingleScatteringSky::getDefaultParameters() {
  SkyParameters parameters;
  parameters.scatteringSamples = 128;
  parameters.opticalDensitySamples = 16;
  parameters.earthRadius = 6360'000.0f;
  parameters.atmosphereRadius = 6420'000.0f;
  parameters.atmosphereThickness = 7994.0f;
  parameters.atmosphereThicknessAerosols = 1200.0f;
  parameters.mieScatteringG = 0.76f;
  parameters.beta = Color(3.8e-6f, 13.5e-6f, 33.1e-6f);
  parameters.betaAerosols = Color(21e-6f);
  parameters.sunColor = Color(20.0f);

  return parameters;
}
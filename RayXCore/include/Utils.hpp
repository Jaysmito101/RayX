#pragma once

#define PI 3.1415926535897932385

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <iostream>

#include "Vec3.hpp"

namespace RayX
{

	const double infinity = std::numeric_limits<double>::infinity();
	const double pi = PI;

	inline double DegreesToRadians(double degrees)
	{
		return degrees * PI / 180.0f;
	}

	inline double RandomDouble()
	{
		return rand() / (RAND_MAX + 1.0);
	}

	inline double RandomDouble(double min, double max)
	{
		return (rand() / (RAND_MAX + 1.0)) * (max - min) + min;
	}

	inline Vec3 RandomVec3()
	{
		return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
	}

	inline Vec3 RandomVec3(double min, double max)
	{
		return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
	}

	inline Vec3 RandomVec3InUnitSphere()
	{
		while (true)
		{
			Vec3 p = RandomVec3(-1, 1);
			if (p.LengthSquared() >= 1) continue;
			return p;
		}
	}

	inline Vec3 RandomUnitVec3()
	{
		return Normalized(RandomVec3());
	}

	inline double Clamp(double x, double min, double max)
	{
		if (x > max) return max;
		if (x < min) return min;
		return x;
	}

	inline Vec3 Reflect(const Vec3& e, const Vec3& n)
	{
		return e - 2 * Dot(e, n) * n;
	}

	inline Vec3 Refract(const Vec3& uv, const Vec3& n, double etaiOverEtat)
	{
		auto cosTheta = fmin(Dot(-uv, n), 1.0);
		Vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);
		Vec3 rOutParallel = -sqrt(abs(1.0 - rOutPerp.LengthSquared())) * n;
		return rOutPerp + rOutParallel;
	}

	template<typename Base, typename T>
	inline bool InstanceOf(const T *ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	template<typename Base, typename T>
	inline bool InstanceOf(std::shared_ptr<T> ptr) {
		return dynamic_cast<const Base*>(ptr.get()) != nullptr;
	}

}

#pragma once

#define PI 3.1415926535897932385

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <iostream>

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

	inline double Clamp(double x, double min, double max)
	{
		if (x > max) return max;
		if (x < min) return min;
		return x;
	}
}

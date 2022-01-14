#pragma once

#include "Vec3.hpp"

namespace RayX
{

	class Ray
	{
	public:
		Ray();

		Ray(const Point3& origin, const Vec3& direction);

		Point3 EvaluateAt(double t) const;

		Point3 mOrigin;
		Vec3 mDirection;
	};

}
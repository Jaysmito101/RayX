#pragma once

#include "Ray.hpp"

namespace RayX
{

	class AABB
	{
	public:
		AABB();

		AABB(Point3 a, Point3 b);

		inline Point3 Min() { return mMinimum; }

		inline Point3 Max() { return mMaximum; }

		bool Hit(Ray& r, double tMin, double tMax);

		Point3 mMinimum;
		Point3 mMaximum;

	};


}
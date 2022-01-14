#pragma once
#include "Hitable.hpp"

namespace RayX
{
	class Sphere : public Hitable
	{
	public:
		Sphere(Point3 center = Point3(0, 0, -1), double radius = 1.0f);

		virtual bool Hit(Ray& r, double tMin, double tMax, HitRecord& rec) override;

		Point3 mCenter;
		double mRadius;
	};
}

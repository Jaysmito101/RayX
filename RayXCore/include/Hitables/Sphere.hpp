#pragma once
#include "Hitable.hpp"

namespace RayX
{
	class Sphere : public Hitable
	{
	public:
		Sphere(Point3 center, double radius, std::shared_ptr<Material> m);

		virtual bool Hit(Ray& r, double tMin, double tMax, HitRecord& rec) override;

		virtual bool BoundingBox(AABB& outputBox) override;


		Point3 mCenter;
		double mRadius;
	};
}

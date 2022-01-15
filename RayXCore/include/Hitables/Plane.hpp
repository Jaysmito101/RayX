#pragma once
#include "Hitable.hpp"

namespace RayX
{
	class Plane : public Hitable
	{
	public:
		Plane(Vec3 normal, double d, std::shared_ptr<Material> m);

		virtual bool Hit(Ray& r, double tMin, double tMax, HitRecord& rec) override;

		Vec3 mNormal;
		double mD;
		std::shared_ptr<Material> mMaterial;
	};
}

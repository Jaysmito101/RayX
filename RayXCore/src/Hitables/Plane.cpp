#include "Hitables/Plane.hpp"

namespace RayX
{
	Plane::Plane(Vec3 normal, Point3 point, std::shared_ptr<Material> mat)
		:mNormal(normal), mPoint(point)
	{
		mMaterial = mat;
	}

	bool Plane::Hit(Ray& r, double tMin, double tMax, HitRecord& rec)
	{
		mD = Dot(mPoint, mNormal); // Ideally should be in Constructor
		auto dDotN = Dot(r.mDirection, mNormal);
		if (abs(dDotN) <= 0.001)
			return false; // If ray is parallel to plane or grazing plane then consider it as not a hit
		auto t = (mD - Dot(r.mOrigin, mNormal)) / dDotN;

		if (t < tMin || tMax < t)
		{
			return false;
		}

		rec.t = t;
		rec.point = r.EvaluateAt(t);
		Vec3 outwardNormal = mNormal;
		rec.SetFaceNormal(r, outwardNormal);
		rec.material = mMaterial;

		return true;
	}

	bool Plane::BoundingBox(AABB& outputBox)
	{
		return false;
	}
}
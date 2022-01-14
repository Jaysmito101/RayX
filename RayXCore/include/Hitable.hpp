#pragma once
#include "Utils.hpp"
#include "Ray.hpp"

namespace RayX
{
	class HitRecord
	{
	public:

		inline void SetFaceNormal(Ray& r, Vec3& outwardNormal)
		{
			frontFace = Dot(r.mDirection, outwardNormal) < 0;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}

		Point3 point;
		Vec3 normal;
		double t;
		bool frontFace;
	};

	class Hitable
	{
	public:
		virtual bool Hit(Ray& r, double tMin, double tMax, HitRecord& rec) = 0;
	};
}
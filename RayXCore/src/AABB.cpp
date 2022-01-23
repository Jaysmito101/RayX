#include "AABB.hpp"

namespace RayX
{

	AABB::AABB()
	{}

	AABB::AABB(Point3 a, Point3 b)
		:mMinimum(a), mMaximum(b)
	{}

	bool AABB::Hit(Ray& r, double tMin, double tMax)
	{
		for (int a = 0; a < 3; a++)
		{
			auto invD = 1.0f / (r.mDirection[a]);
			auto t0 = (mMinimum[a] - r.mOrigin[a]) * invD;
			auto t1 = (mMaximum[a] - r.mOrigin[a]) * invD;

			if (invD < 0.0f)
				std::swap(t0, t1);

			tMin = t0 > tMin ? t0 : tMin;
			tMax = t1 < tMax ? t1 : tMax;

			if (tMax <= tMin)
				return false;
		}
		return true;
	}
}
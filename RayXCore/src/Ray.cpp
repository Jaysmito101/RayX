#include "Ray.hpp"

namespace RayX
{

	Ray::Ray()
		:mOrigin(0), mDirection(0)
	{}

	Ray::Ray(const Point3& origin, const Vec3& direction)
		:mOrigin(origin), mDirection(direction)
	{}

	Point3 Ray::EvaluateAt(double t) const
	{
		return mOrigin + t * mDirection;
	}


}
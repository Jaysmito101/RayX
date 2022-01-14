#pragma once

#include "Ray.hpp"

namespace RayX
{
	class Camera
	{
	public:

		Camera(double aspectRatio = 16.0/9.0, double focalLength = 1.0);

		Ray GetRay(double u, double v);

		Point3 mOrigin;
		Point3 mLowerLeftCorner;
		Vec3 mHorizontal;
		Vec3 mVertical;

		double mAspectRatio;
		double mFocalLength;
	};
}

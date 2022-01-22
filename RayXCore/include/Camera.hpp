#pragma once

#include "Ray.hpp"

namespace RayX
{
	class Camera
	{
	public:

		Camera();

		void Update();

		Ray GetRay(double u, double v);

		Point3 mLookFrom;
		Point3 mLookAt;
		Vec3 mVUp;

		Point3 mOrigin;
		Point3 mLowerLeftCorner;
		Vec3 mHorizontal;
		Vec3 mVertical;

		double mAspectRatio;
		double mVfov;
	};
}

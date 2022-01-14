#include "Camera.hpp"
#include "Utils.hpp"

namespace RayX
{
	Camera::Camera(double aspectRatio, double focalLength)
		:mAspectRatio(aspectRatio), mFocalLength(focalLength)
	{
		double viewportHeight = 2.0f;
		double viewportWidth = viewportHeight * aspectRatio;

		mOrigin = Point3(0);

		mHorizontal = Vec3(viewportWidth, 0, 0);
		mVertical = Vec3(0, viewportHeight, 0);
		mLowerLeftCorner = mOrigin - mHorizontal / 2 - mVertical / 2 - Vec3(0, 0, focalLength);
	}

	Ray Camera::GetRay(double u, double v)
	{
		return Ray(mOrigin, mLowerLeftCorner + u * mHorizontal + v * mVertical - mOrigin);
	}

}
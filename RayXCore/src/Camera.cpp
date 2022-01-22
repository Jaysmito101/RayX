#include "Camera.hpp"
#include "Utils.hpp"

namespace RayX
{
	Camera::Camera()
	{
		mAspectRatio = 16.0 / 9.0;
		mOrigin = Point3(0);
		mVfov = 90;

		mLookFrom = Point3(0);
		mLookAt = Point3(1);
		mVUp = Point3(0, 1, 0);
	}

	void Camera::Update()
	{
		auto theta = DegreesToRadians(mVfov);
		auto h = tan(theta / 2);

		auto viewportHeight = 2 * h;

		auto viewportWidth = mAspectRatio * viewportHeight;

		auto w = Normalized(mLookFrom - mLookAt);
		auto u = Normalized(Cross(mVUp, w));
		auto v = Cross(w, u);

		mOrigin = mLookFrom;
		mHorizontal = viewportWidth * u;
		mVertical = viewportHeight * v;
		mLowerLeftCorner = mOrigin - mHorizontal / 2 - mVertical / 2 - w;

	}

	Ray Camera::GetRay(double s, double t)
	{
		return Ray(mOrigin, mLowerLeftCorner + s * mHorizontal + t * mVertical - mOrigin);
	}

}
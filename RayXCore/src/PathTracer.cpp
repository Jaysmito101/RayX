#include "PathTracer.hpp"

#include <iostream>
#include <chrono>

namespace RayX
{

PathTracer::PathTracer(int width, int height)
: mImageWidth(width), mImageHeight(height), mIsRendering(false), mRenderProgress(0.0f)
{

}

PathTracer::~PathTracer()
{
}

void PathTracer::Render(std::shared_ptr<Image> image, std::function<void(float)> callback)
{
    mRenderProgress = 0.0f;
    mIsRendering = true;

    int imageWidth = image->mImageWidth;
    int imageHeight = image->mImageHeight;

    double aspectRatio = (double)imageWidth / imageHeight;
    double viewportHeight = 2.0;
    double viewportWidth = aspectRatio * viewportHeight;
    double focalLength = 1.0;

    auto origin = Point3(0);
    auto horizontal = Vec3(viewportWidth, 0, 0);
    auto vertical = Vec3(0, viewportHeight, 0);

    auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);
    
    int c = 0;

    for (int j = imageHeight - 1; j >= 0; j--)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            auto u = double(i) / (imageWidth - 1);
            auto v = double(j) / (imageHeight - 1);
            Ray r(origin, lowerLeftCorner + u*horizontal + v * vertical - origin);
            Color pixelColor = Trace(r);
            image->SetPixel(i, imageHeight - j, pixelColor);

            c++;
            if (j % 10 == 0)
            {
                mRenderProgress = ((float)c) / (imageHeight * imageWidth);
                callback(mRenderProgress);
                std::this_thread::sleep_for(std::chrono::nanoseconds(100));
            }
        }
    }

    mRenderProgress = 1.0f;
    mIsRendering = false;
}

static bool HitSphere(const Point3& center, const double radius, Ray& r)
{
    Vec3 oc = r.mOrigin - center;
    auto a = r.mDirection.LengthSquared();
    auto b = 2 * Dot(oc, r.mDirection);
    auto c = oc.LengthSquared() - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return discriminant > 0;
}

Color PathTracer::Trace(Ray& r)
{
    if (HitSphere(Point3(0, 0, -1), 0.5, r))
        return Color(1,0,0);

    Vec3 dir = Normalized(r.mDirection);
    auto t = 0.5 * (dir.y + 1);

    return (1 - t) * Color(1) + t * Color(0.5, 0.7, 1.0);
}

} // namespace RayX
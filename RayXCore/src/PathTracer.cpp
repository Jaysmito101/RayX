#include "PathTracer.hpp"
#include "Utils.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Hitables/Sphere.hpp"

#include <iostream>
#include <chrono>


namespace RayX
{

PathTracer::PathTracer(int width, int height)
: mImageWidth(width), mImageHeight(height), mIsRendering(false), mRenderProgress(0.0f), mSamplesPerPixel(100)
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
   
    Camera cam((double)imageWidth/imageHeight);

    World world;
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    int c = 0;

    for (int j = imageHeight - 1; j >= 0; j--)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            Color pixelColor;
            Ray r;
            for (int s = 0; s < mSamplesPerPixel; s++)
            {
                auto u = double(i + RandomDouble()) / (imageWidth - 1);
                auto v = double(j + RandomDouble()) / (imageHeight - 1);
                r = cam.GetRay(u, v);
                pixelColor += Trace(r, world);
            }
            pixelColor /= mSamplesPerPixel;
            image->SetPixel(i, imageHeight - j, pixelColor);

            c++;
            if (j % 10 == 0)
            {
                mRenderProgress = ((float)c) / (imageHeight * imageWidth);
                callback(mRenderProgress);
            }
        }
    }

    mRenderProgress = 1.0f;
    mIsRendering = false;
}


Color PathTracer::Trace(Ray& r, World& world)
{
    HitRecord rec;

    if (world.Hit(r, 0, infinity, rec))
    {

        return 0.5 * (rec.normal + Color(1));
    }

    Vec3 dir = Normalized(r.mDirection);
    auto t = 0.5 * (dir.y + 1);
    return (1 - t) * Color(1) + t * Color(0.5, 0.7, 1.0);
}

} // namespace RayX
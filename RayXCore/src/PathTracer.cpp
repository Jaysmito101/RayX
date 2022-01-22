#include "PathTracer.hpp"
#include "Utils.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Hitables/Sphere.hpp"
#include "Hitables/Plane.hpp"
#include "Material.hpp"
#include "Materials/Lambertian.hpp"
#include "Materials/Metal.hpp"
#include "Materials/Dielectric.hpp"

#include <iostream>
#include <chrono>


namespace RayX
{

PathTracer::PathTracer(int width, int height)
: mImageWidth(width), mImageHeight(height), mIsRendering(false), mRenderProgress(0.0f), mSamplesPerPixel(50), mMaxBounces(25)
{
    mCancelRendering = false;
}

PathTracer::~PathTracer()
{
}

void PathTracer::Render(std::shared_ptr<Image> image, std::function<void(float)> callback)
{
    mRenderProgress = 0.0f;
    mCancelRendering = false;
    mIsRendering = true;

    int imageWidth = image->mImageWidth;
    int imageHeight = image->mImageHeight;
   
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
                r = mCamera.GetRay(u, v);
                pixelColor += Trace(r, mWorld, mMaxBounces);
            }
            pixelColor /= mSamplesPerPixel;
            image->SetPixel(i, imageHeight - j, pixelColor);

            c++;
            if (j % 10 == 0)
            {
                if (mCancelRendering) 
                {
                    mIsRendering = false;
                    return;
                }
                mRenderProgress = ((float)c) / (imageHeight * imageWidth);
                callback(mRenderProgress);
            }
        }
    }

    mRenderProgress = 1.0f;
    mIsRendering = false;
}


Color PathTracer::Trace(Ray& r, World& mWorld, int depth)
{
    HitRecord rec;

    if (depth <= 0)
        return Color(0);

    if (mWorld.Hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Color attenuation;
        if(rec.material->Scatter(r, rec, attenuation, scattered))
            return attenuation * Trace(scattered, mWorld, depth - 1);
        return Color(0);
    }

    Vec3 dir = Normalized(r.mDirection);
    auto t = 0.5 * (dir.y + 1);
    return (1 - t) * Color(1) + t * Color(0.5, 0.7, 1.0);
}

} // namespace RayX
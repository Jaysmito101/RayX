#include "PathTracer.hpp"
#include "Utils.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Hitable.hpp"
#include "BVHNode.hpp"
#include "Material.hpp"

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

    if (mOnStatusMessages)
        mOnStatusMessages("Starting BVH Construction");
    
    World world(std::make_shared<BVHNode>(mWorld));

    if (mOnStatusMessages)
    {
        mOnStatusMessages("Finished BVH Construction");
        mOnStatusMessages("Started Rendering");
    }

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
                pixelColor += Trace(r, world, mMaxBounces);
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

    callback(1.0f);

    if (mOnStatusMessages)
        mOnStatusMessages("Finished Rendering");

    mRenderProgress = 1.0f;
    mIsRendering = false;
}


Color PathTracer::Trace(Ray& r, World& world, int depth)
{
    HitRecord rec;

    if (depth <= 0)
        return Color(0);

    if (world.Hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Color attenuation;
        if(rec.material->Scatter(r, rec, attenuation, scattered))
            return attenuation * Trace(scattered, world, depth - 1);
        return Color(0);
    }

    Vec3 dir = Normalized(r.mDirection);
    auto t = 0.5 * (dir.y + 1);
    return (1 - t) * Color(1) + t * Color(0.5, 0.7, 1.0);
}

} // namespace RayX
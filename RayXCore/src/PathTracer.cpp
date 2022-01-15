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
   
    Camera cam((double)imageWidth/imageHeight);

    World world;

    auto mat1 = std::make_shared<Lambertian>(Color(0.8, 0.8, 0));
    auto mat2 = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto mat3 = std::make_shared<Dielectric>(1.5);
    auto mat4 = std::make_shared<Metal>(Color(0.2, 0.8, 0.4), 0.3);

    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, mat1));
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, mat2));
    world.Add(std::make_shared<Sphere>(Point3(-1, 0.05, -1), 0.5, mat3));
    world.Add(std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, mat4));
    world.Add(std::make_shared<Plane>(Vec3(0.2932, 0.0733, 0.0973), 0.3, mat4));

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
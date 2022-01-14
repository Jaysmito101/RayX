
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <functional>

#include "Vec3.hpp"
#include "Image.hpp"
#include "Ray.hpp"
#include "World.hpp"

namespace RayX
{

    class PathTracer 
    {
    public:
        PathTracer(int width, int height);
        ~PathTracer();

        void Render(std::shared_ptr<Image> image, std::function<void(float)> callback = [] (float) {});

    protected:
        Color Trace(Ray& r, World& world, int depth);

    public:
        std::atomic<bool> mIsRendering;
        std::atomic<bool> mCancelRendering;
        float mRenderProgress;    
        int mImageWidth;
        int mImageHeight;
        int mSamplesPerPixel;
        int mMaxBounces;
        
    }; // class PathTracer
    
} // namespace RayX
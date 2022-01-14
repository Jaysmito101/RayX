
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <functional>

#include "Vec3.hpp"
#include "Image.hpp"
#include "Ray.hpp"

namespace RayX
{

    class PathTracer 
    {
    public:
        PathTracer(int width, int height);
        ~PathTracer();

        void Render(std::shared_ptr<Image> image, std::function<void(float)> callback = [] (float) {});

    protected:
        Color Trace(Ray& r);

    public:
        std::atomic<bool> mIsRendering;
        float mRenderProgress;    
        int mImageWidth;
        int mImageHeight;
    }; // class PathTracer
    
} // namespace RayX
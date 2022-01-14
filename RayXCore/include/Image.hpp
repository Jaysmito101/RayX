#pragma once

#include <atomic>

#include "Vec3.hpp"

namespace RayX
{
    class Image
    {
        public:

            Image();

            ~Image();

            void SetPixel(int x, int y, Color color);

            Color GetPixel(int x, int y);

            void Resize(int width, int height);

        int mImageWidth, mImageHeight;
        std::atomic<bool> mIsPixelSetting;
        unsigned char* mImageData;
    }; // class Image

} // namespace RayX
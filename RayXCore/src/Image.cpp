#include "Image.hpp"
#include "Utils.hpp"

namespace RayX
{

    static constexpr double colorScale = 1.0 / 255.0;

    Image::Image()
    {
        mImageData = nullptr;
    }

    Image::~Image()
    {
        if (mImageData)
            delete[] mImageData;
    }

    void Image::SetPixel(int x, int y, Color color)
    {
        // Gamma Correction
        color.x = sqrt(color.x);
        color.y = sqrt(color.y);
        color.z = sqrt(color.z);

        mIsPixelSetting = true;
        unsigned char* offset = mImageData + (x * 3 + mImageWidth * y * 3);
        offset[0] = static_cast<unsigned char>(Clamp(color.x, 0, 0.999) * 255.999);
        offset[1] = static_cast<unsigned char>(Clamp(color.y, 0, 0.999) * 255.999);
        offset[2] = static_cast<unsigned char>(Clamp(color.z, 0, 0.999) * 255.999);
        mIsPixelSetting = false;
    }

    Color Image::GetPixel(int x, int y)
    {
        Color col;
        mIsPixelSetting = true;
        unsigned char* offset = mImageData + (x * 3 + mImageWidth * y * 3);
        col.x = offset[0] * colorScale;
        col.y = offset[1] * colorScale;
        col.z = offset[2] * colorScale;
        mIsPixelSetting = false;
        return col;
    }
    
    void Image::Resize(int width, int height)
    {
        mIsPixelSetting = true;
        if (mImageData)
            delete[] mImageData;
        mImageWidth = width;
        mImageHeight = height;
        mImageData = new unsigned char[width * height * 3];
        memset(mImageData, 0, width * height * 3);
        mIsPixelSetting = false;
    }

} // namespace RayX
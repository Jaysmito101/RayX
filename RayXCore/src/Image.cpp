#include "Image.hpp"
#include "Utils.hpp"

namespace RayX
{

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
        col.x = offset[0];
        col.y = offset[1];
        col.z = offset[2];
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
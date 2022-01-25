#include "Textures/ImageTexture.hpp"
#include "Utils.hpp"

namespace RayX
{

	ImageTexture::ImageTexture(std::shared_ptr<Image> image)
		:mImage(image)
	{}

	Color ImageTexture::EvaluateAt(double u, double v, Point3& p)
	{
		if (!mImage)
			return Color(0, 1, 1);

		u = Clamp(u, 0, 1);
		v = 1 - Clamp(v, 0, 1);

		auto i = static_cast<int>(u * mImage->mImageWidth);
		auto j = static_cast<int>(u * mImage->mImageHeight);

		if (i >= mImage->mImageWidth)
			i = mImage->mImageWidth - 1;

		if (j > mImage->mImageHeight)
			j = mImage->mImageHeight - 1;

		return mImage->GetPixel(i, j);
	}

}
#pragma once

#include "Texture.hpp"
#include "Image.hpp"

namespace RayX
{

	class ImageTexture : public Texture
	{
	public:

		ImageTexture(std::shared_ptr<Image> image);

		virtual Color EvaluateAt(double u, double v, Point3& p) override;

		std::shared_ptr<Image> mImage;
	};

}

#pragma once

#include "Texture.hpp"

namespace RayX
{

	class CheckerTexture : public Texture
	{
	public:

		CheckerTexture();

		CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);

		virtual Color EvaluateAt(double u, double v, Point3& p) override;

		std::shared_ptr<Texture> mOdd;
		std::shared_ptr<Texture> mEven;

	};

}

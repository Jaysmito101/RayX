#include "Textures/CheckerTexture.hpp"
#include "Textures/SolidColor.hpp"
#include "Utils.hpp"

namespace RayX
{

	CheckerTexture::CheckerTexture()
		:mEven(std::make_shared<SolidColor>(Color(0.2))), mOdd(std::make_shared<SolidColor>(Color(0.8)))
	{}

	CheckerTexture::CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
		:mEven(even), mOdd(odd)
	{}

	Color CheckerTexture::EvaluateAt(double u, double v, Point3 & p)
	{
		auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
		if (sines < 0)
			return mOdd->EvaluateAt(u, v, p);
		else
			return mEven->EvaluateAt(u, v, p);
	}
}
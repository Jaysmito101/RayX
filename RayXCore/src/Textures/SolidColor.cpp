#include "Utils.hpp"
#include "Textures/SolidColor.hpp"

namespace RayX
{

	SolidColor::SolidColor()
		: mColor(0, 0, 0)
	{}

	SolidColor::SolidColor(Color c)
		: mColor(c)
	{}

	SolidColor::SolidColor(double r, double g, double b)
		: mColor(r, g, b)
	{}

	Color SolidColor::EvaluateAt(double u, double v, Point3& p)
	{
		return mColor;
	}

}

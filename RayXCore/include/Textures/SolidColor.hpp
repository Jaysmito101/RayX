#pragma once

#include "Texture.hpp"

namespace RayX
{

	class SolidColor : public Texture
	{
	public:
		
		SolidColor();

		SolidColor(Color c);

		SolidColor(double r, double g, double b);

		virtual Color EvaluateAt(double u, double v, Point3& p) override;

	public:
		Color mColor;
	};

}

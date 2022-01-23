#pragma once

#include "Vec3.hpp"

namespace RayX 
{

	class Texture
	{
	public:
		virtual Color EvaluateAt(double u, double v, Point3& p) = 0;
	};

}
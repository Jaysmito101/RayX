#pragma once

#include "Utils.hpp"
#include "Ray.hpp"



namespace RayX
{

	class Texture;

	class HitRecord;

	class Material
	{
	public:
		virtual bool Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered) = 0;

	};

}

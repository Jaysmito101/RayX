#pragma once

#include "Material.hpp"
#include "Utils.hpp"

namespace RayX
{
	class Metal : public Material
	{
	public:
		Metal(Color col, double f);

		virtual bool Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered);

	public:
		Color albedo;
		double mFuzz;
	};
}
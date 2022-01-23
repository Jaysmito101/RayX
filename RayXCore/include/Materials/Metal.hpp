#pragma once

#include "Material.hpp"
#include "Utils.hpp"

namespace RayX
{
	class Metal : public Material
	{
	public:
		
		Metal(Color col, double f);

		Metal(std::shared_ptr<Texture> texure, double f);

		virtual bool Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered);

	public:
		std::shared_ptr<Texture> mColor;
		double mFuzz;
	};
}
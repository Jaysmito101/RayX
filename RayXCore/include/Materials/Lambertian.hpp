#pragma once

#include "Material.hpp"

namespace RayX
{

	class Lambertian : public Material
	{
	public:
		Lambertian(Color col);

		virtual bool Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered) override;

	public:
		Color albedo;
	};

}

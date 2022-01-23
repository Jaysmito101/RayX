#pragma once

#include "Material.hpp"

namespace RayX
{

	class Lambertian : public Material
	{
	public:
		Lambertian(Color col);

		Lambertian(std::shared_ptr<Texture> texture);

		virtual bool Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered) override;

	public:
		std::shared_ptr<Texture> mAlbedo;
	};

}

#include "Materials/Lambertian.hpp"
#include "Hitable.hpp"
#include "Textures/SolidColor.hpp"
#include "Texture.hpp"

namespace RayX
{
	Lambertian::Lambertian(Color col)
		:mAlbedo(std::make_shared<SolidColor>(col))
	{
	}

	Lambertian::Lambertian(std::shared_ptr<Texture> texture)
		: mAlbedo(texture)
	{
	}

	bool Lambertian::Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered)
	{
		auto scatterDir = rec.normal + RandomUnitVec3();

		if (scatterDir.IsNearZero())
			scatterDir = rec.normal;

		rScattered = Ray(rec.point, scatterDir);
		attenuation = mAlbedo->EvaluateAt(rec.u, rec.v, rec.point);
		return true;
	}
}
#include "Materials/Lambertian.hpp"
#include "Hitable.hpp"

namespace RayX
{
	Lambertian::Lambertian(Color col)
	{
		albedo = col;
	}

	bool Lambertian::Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered)
	{
		auto scatterDir = rec.normal + RandomUnitVec3();

		if (scatterDir.IsNearZero())
			scatterDir = rec.normal;

		rScattered = Ray(rec.point, scatterDir);
		attenuation = albedo;
		return true;
	}
}
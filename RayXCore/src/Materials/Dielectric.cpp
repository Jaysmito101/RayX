#include "Materials/Dielectric.hpp"
#include "Hitable.hpp"

namespace RayX
{

	Dielectric::Dielectric(double refractiveIndex)
		:mIr(refractiveIndex)
	{}

	bool Dielectric::Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered)
	{
		attenuation = Color(1.0);

		double refractionRatio = rec.frontFace ? (1.0 / mIr) : mIr;
		Vec3 dir = Normalized(rIn.mDirection);

		double cosTheta = fmin(Dot(-dir, rec.normal), 1.0);
		double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

		bool cannotRefract = refractionRatio * sinTheta > 1.0;

		Vec3 direction;
		if (cannotRefract || Reflectance(cosTheta, refractionRatio) > RandomDouble())
			direction = Reflect(dir, rec.normal);
		else
			direction = Refract(dir, rec.normal, refractionRatio);

		rScattered = Ray(rec.point, direction);
		return true;
	}

	double Dielectric::Reflectance(double cosine, double refIdx)
	{
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - refIdx) / (1 + refIdx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

}
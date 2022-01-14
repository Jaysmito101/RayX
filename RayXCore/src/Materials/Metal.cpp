#include "Materials/Metal.hpp"
#include "Hitable.hpp"

namespace RayX
{
	Metal::Metal(Color col, double f)
	{
		albedo = col;
		mFuzz = f;
	}

	bool Metal::Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered)
	{
		Vec3 reflected = Reflect(Normalized(rIn.mDirection), rec.normal);
		rScattered = Ray(rec.point, reflected + mFuzz * RandomVec3InUnitSphere());
		attenuation = albedo;
		return Dot(rScattered.mDirection, rec.normal) > 0;
	}
}
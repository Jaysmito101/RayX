#include "Materials/Metal.hpp"
#include "Hitable.hpp"
#include "Textures/SolidColor.hpp"

namespace RayX
{
	Metal::Metal(Color col, double f)
		:mColor(std::make_shared<SolidColor>(col)), mFuzz(f)
	{
	}

	Metal::Metal(std::shared_ptr<Texture> texure, double f)
		:mFuzz(f), mColor(texure)
	{
	}

	bool Metal::Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered)
	{
		Vec3 reflected = Reflect(Normalized(rIn.mDirection), rec.normal);
		rScattered = Ray(rec.point, reflected + mFuzz * RandomVec3InUnitSphere());
		attenuation = mColor->EvaluateAt(rec.u, rec.v, rec.point);
		return Dot(rScattered.mDirection, rec.normal) > 0;
	}
}
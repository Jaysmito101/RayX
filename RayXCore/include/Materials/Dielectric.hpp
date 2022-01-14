#pragma once

#include "Material.hpp"

namespace RayX
{

	class Dielectric : public Material
	{
	public:

		Dielectric(double refractiveIndex);

		virtual bool Scatter(Ray& rIn, HitRecord& rec, Color& attenuation, Ray& rScattered);

	public:
		double mIr;

	private:
		static double Reflectance(double cosine, double refIdx);
	};

}

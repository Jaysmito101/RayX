#include "Hitables/Plane.hpp"

namespace RayX
{
	Plane::Plane(Vec3 normal, double d, std::shared_ptr<Material> mat)
		:mNormal(normal), mD(d), mMaterial(mat)
	{}

	bool Plane::Hit(Ray& r, double tMin, double tMax, HitRecord& rec)
	{
        auto dDotN = Dot(r.mDirection, mNormal);
	if(dDotN == 0) return false;
        auto t = (mD - Dot(r.mOrigin, mNormal)) / dDotN;

        if (t < tMin || tMax < t)
        {
            return false;
        }

        rec.t = t;
        rec.point = r.EvaluateAt(t);
        Vec3 outwardNormal = mNormal;
        rec.SetFaceNormal(r, outwardNormal);
        rec.material = mMaterial;

        return true;
	}
}
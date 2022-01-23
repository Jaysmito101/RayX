#include "Hitables/Sphere.hpp"
#include "Utils.hpp"

namespace RayX
{
	Sphere::Sphere(Point3 center, double radius, std::shared_ptr<Material> mat)
		:mCenter(center), mRadius(radius)
	{mMaterial = mat;}

	bool Sphere::Hit(Ray& r, double tMin, double tMax, HitRecord& rec)
	{
        Vec3 oc = r.mOrigin - mCenter;
        auto a = r.mDirection.LengthSquared();
        auto halfB = Dot(oc, r.mDirection);
        auto c = oc.LengthSquared() - mRadius * mRadius;
        auto discriminant = halfB * halfB - a * c;
        if (discriminant < 0)
        {
            return false;
        }

        auto sqrtd = sqrt(discriminant);        
        auto root = (-halfB - sqrtd) / a;
        if (root < tMin || tMax < root)
        {
            root = (-halfB + sqrtd) / a;
            if (root < tMin || tMax < root)
                return false;
        }

        rec.t = root;
        rec.point = r.EvaluateAt(root);
        Vec3 outwardNormal = (rec.point - mCenter) / mRadius;
        rec.SetFaceNormal(r, outwardNormal);
        GetSphereUV(outwardNormal, rec.u, rec.v);
        rec.material = mMaterial;

        return true;
	}
    
    bool Sphere::BoundingBox(AABB& outputBox)
    {
        outputBox = AABB(
            mCenter - Vec3(mRadius, mRadius, mRadius),
            mCenter + Vec3(mRadius, mRadius, mRadius));
        return true;
    }

    void Sphere::GetSphereUV(Point3& p, double& u, double& v)
    {
        auto theta = acos(-p.y);
        auto phi = atan2(-p.z, p.x) + PI;

        u = phi / (2 * PI);
        v = theta / pi;
    }
}
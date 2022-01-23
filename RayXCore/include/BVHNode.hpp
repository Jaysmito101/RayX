#pragma once

#include "Utils.hpp"
#include "World.hpp"

namespace RayX
{

	class BVHNode : public Hitable
	{
	public:


		BVHNode(World& world);

		BVHNode(std::vector<std::shared_ptr<Hitable>>& hitables, size_t start, size_t end);

		virtual bool Hit(Ray& r, double tMin, double tMax, HitRecord& rec) override;

		virtual bool BoundingBox(AABB& outputBox) override;

		std::shared_ptr<Hitable> mLeft;
		std::shared_ptr<Hitable> mRight;
		AABB mBox;
	};

}

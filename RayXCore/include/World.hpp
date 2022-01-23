#pragma once

#include "Hitable.hpp"
#include "AABB.hpp"

#include <memory>
#include <vector>

namespace RayX
{
	class World : public Hitable
	{
	public:
		
		World();

		World(std::shared_ptr<Hitable> obj);

		inline void Clear() { mHitables.clear(); }

		inline void Add(std::shared_ptr<Hitable> obj) { mHitables.push_back(obj); }

		virtual bool Hit(Ray& r, double tMin, double tMax, HitRecord& rec) override;

		virtual bool BoundingBox(AABB& outputBox) override;


		std::vector<std::shared_ptr<Hitable>> mHitables;
	};
}

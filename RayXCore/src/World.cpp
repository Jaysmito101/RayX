#include "World.hpp"
#include "Utils.hpp"

namespace RayX
{

	World::World()
	{}

	World::World(std::shared_ptr<Hitable> obj)
	{
		mHitables.push_back(obj);
	}

	bool World::Hit(Ray& r, double tMin, double tMax, HitRecord& rec)
	{
		HitRecord tmp;

		bool hitAnything = false;

		auto closestSoFar = tMax;

		for (auto& obj : mHitables)
		{
			if (obj->Hit(r, tMin, closestSoFar, tmp))
			{
				hitAnything = true;
				closestSoFar = tmp.t;
				rec = tmp;
			}
		}

		return hitAnything;
	}

	bool World::BoundingBox(AABB& outputBox)
	{
		if (mHitables.empty())
			return false;

		AABB tmp;
		bool firstBox = true;

		for (auto& hitable : mHitables)
		{
			if (!hitable->BoundingBox(tmp))
				return false;
			outputBox = firstBox ? tmp : SurroundingBox(outputBox, tmp);
			firstBox = false;
		}

		return true;
	}

}
#include "World.hpp"

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

}
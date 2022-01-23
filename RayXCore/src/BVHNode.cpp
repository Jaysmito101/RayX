#include "BVHNode.hpp"

#include <algorithm>

namespace RayX
{

	inline bool BoxCompare(std::shared_ptr<Hitable> a, std::shared_ptr<Hitable> b, int axis)
	{
		AABB boxA;
		AABB boxB;

		if (!a->BoundingBox(boxA) || !b->BoundingBox(boxB))
			std::cerr << "No Bounding box!\n";

		return boxA.mMinimum[axis] < boxB.mMinimum[axis];
	}

	static bool BoxCompareX(std::shared_ptr<Hitable> a, std::shared_ptr<Hitable> b)
	{
		return BoxCompare(a, b, 0);
	}

	static bool BoxCompareY(std::shared_ptr<Hitable> a, std::shared_ptr<Hitable> b)
	{
		return BoxCompare(a, b, 1);
	}

	static bool BoxCompareZ(std::shared_ptr<Hitable> a, std::shared_ptr<Hitable> b)
	{
		return BoxCompare(a, b, 2);
	}

	BVHNode::BVHNode(World& world)
		:BVHNode(world.mHitables, 0, world.mHitables.size())
	{}


	BVHNode::BVHNode(std::vector<std::shared_ptr<Hitable>>& srcHitables, size_t start, size_t end)
	{
		auto hitables = srcHitables;

		int axis = RandomInt(0, 2);
		auto comparator = (axis == 0) ? BoxCompareX
			: (axis == 1) ? BoxCompareY
			: BoxCompareZ;

		size_t hitableSpan = end - start;

		if (hitableSpan == 1)
			mLeft = mRight = hitables[start];
		else if (hitableSpan == 2)
		{
			if (comparator(hitables[start], hitables[start + 1]))
			{
				mLeft = hitables[start];
				mRight = hitables[start + 1];
			}
			else
			{
				mLeft = hitables[start + 1];
				mRight = hitables[start];
			}
		}
		else
		{
			std::sort(hitables.begin() + start, hitables.begin() + end, comparator);

			auto mid = start + hitableSpan / 2;
			mLeft = std::make_shared<BVHNode>(hitables, start, mid);
			mRight = std::make_shared<BVHNode>(hitables, mid, end);
		}

		AABB boxLeft, boxRight;

		if (!mLeft->BoundingBox(boxLeft) || !mRight->BoundingBox(boxRight))
			std::cerr << "No Bounding Box in BVH Node Constructor.";

		mBox = SurroundingBox(boxLeft, boxRight);
	}

	bool BVHNode::Hit(Ray& r, double tMin, double tMax, HitRecord& rec)
	{
		if (!mBox.Hit(r, tMin, tMax))
			return false;

		bool hitLeft = mLeft->Hit(r, tMin, tMax, rec);
		bool hitRight = mRight->Hit(r, tMin, hitLeft ? rec.t : tMax, rec);

		return hitLeft || hitRight;
	}

	bool BVHNode::BoundingBox(AABB& outputBox)
	{
		outputBox = mBox;
		return true;
	}
}
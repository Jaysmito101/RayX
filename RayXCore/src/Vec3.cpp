#include "Vec3.hpp"

namespace RayX
{

	Vec3::Vec3()
		:x(0), y(0), z(0)
	{}

	Vec3::Vec3(double v)
		: x(v), y(v), z(v)
	{}

	Vec3::Vec3(double x, double y)
		: x(x), y(y), z(0)
	{}

	Vec3::Vec3(double x, double y, double z)
		: x(x), y(y), z(z)
	{}

}
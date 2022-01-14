#pragma once

#include <cmath>
#include <iostream>

namespace RayX
{

	class Vec3
	{
	public:

		Vec3();

		Vec3(double v);

		Vec3(double x, double y);

		Vec3(double x, double y, double z);

		inline bool IsNearZero()
		{
			const auto s = 1e-8;
			return (abs(x) < s) && (abs(y) < s) && (abs(z) < s);
		}

		inline Vec3 operator-() const 
		{
			return Vec3(-x, -y, -z);
		}

		inline double operator[](int i) const
		{
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default : return 0;
			}
		}

		inline double& operator[](int i)
		{
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: return x;
			}
		}

		inline Vec3& operator=(const Vec3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		

		inline Vec3& operator+=(const Vec3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		inline Vec3& operator*=(const double v)
		{
			x *= v;
			y *= v;
			z *= v;
			return *this;
		}

		inline Vec3& operator/=(const double v)
		{
			x /= v;
			y /= v;
			z /= v;
			return *this;
		}

		inline double Length() const
		{
			return sqrt(x*x + y*y + z*z);
		}

		inline double LengthSquared() const
		{
			return (x * x + y * y + z * z);
		}

	public:
		double x, y, z;
	};

	using Point3 = Vec3;
	using Color = Vec3;

	inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
		return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
	
	inline Vec3 operator+(const Vec3& u, const Vec3& v) {
		return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
	}
	
	inline Vec3 operator-(const Vec3& u, const Vec3& v) {
		return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
	}
	
	inline Vec3 operator*(const Vec3& u, const Vec3& v) {
		return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
	}
	
	inline Vec3 operator*(double t, const Vec3& v) {
		return Vec3(t * v.x, t * v.y, t * v.z);
	}
	
	inline Vec3 operator*(const Vec3& v, double t) {
		return t * v;
	}
	
	inline Vec3 operator/(Vec3 v, double t) {
		return (1 / t) * v;
	}
	
	inline double Dot(const Vec3& u, const Vec3& v) {
		return u.x * v.x
			+ u.y * v.y
			+ u.z * v.z;
	}
	
	inline Vec3 Cross(const Vec3& u, const Vec3& v) {
		return Vec3(u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
	}
	
	inline Vec3 Normalized(Vec3 v){
		return v / v.Length();
	}
	
	inline Vec3& Normalize(Vec3& v)
	{
		v /= v.Length();
		return v;
	}
}
#pragma once
#include"Vector2.h"
#include"VectorUtility.h"

struct Vector3
{
	const static Vector3 Zero;
	const static Vector3 One;
	const static Vector3 Up;
	const static Vector3 Down;
	const static Vector3 Right;
	const static Vector3 Left;
	const static Vector3 Front;
	const static Vector3 Back;

	static Vector3 FromString(std::string s);
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	union
	{
		struct
		{
			float x, y, z;
		};
		struct
		{
			Vector2 v2d;
			float z;
		};
	};
	Vector3()
		:x(0.0f), y(0.0f), z(0.0f)
	{

	}
	Vector3(float x, float y, float z = 0.0f)
		:x(x), y(y), z(z)
	{

	}
	Vector3& operator=(const Vector2& v)
	{
		v2d = v;
		return *this;
	}
	Vector3& operator=(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	bool operator==(const Vector3& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}
	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}
	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3 operator*(float f) const
	{
		return Vector3(f * x, f * y, f * z);
	}
	Vector3 operator/(float f) const
	{
		return Vector3(x / f, y / f, z / f);
	}

	float SqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}
	float Magnitude() const
	{
		return sqrtf(x * x + y * y + z * z);
	}
	Vector3& Normalize()
	{
		float f = Magnitude();
		if (f != 0)
		{
			x /= f;
			y /= f;
			z /= f;
		}
		return *this;
	}
	Vector3 Normalize() const
	{
		float f = Magnitude();
		if (f == 0)
			return Vector3::Zero;
		return Vector3(x / f, y / f, z / f);
	}
};

inline Vector3 operator*(float f, const Vector3& v)
{
	return Vector3(f * v.x, f * v.y, f * v.z);
}
inline std::ostream& operator<<(std::ostream& stream, const Vector3& v)
{
	stream << "(" << v.x << "," << v.y << "," << v.z << ")";
	return stream;
}

namespace std
{
	template <>
	struct hash<Vector3>
	{
		size_t operator()(const Vector3& v) const
		{
			return hash<float>()(v.x) ^ hash<float>()((v.y)) ^ hash<float>()((v.z));
		}
	};
}
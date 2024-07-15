#pragma once
#include"VectorUtility.h"
#include<ctype.h>

struct Vector2Int
{
	static Vector2Int FromString(std::string s);

	const static Vector2Int Zero;
	const static Vector2Int One;
	const static Vector2Int Up;
	const static Vector2Int Down;
	const static Vector2Int Right;
	const static Vector2Int Left;

	int x, y;
	Vector2Int()
		:x(0), y(0)
	{

	}
	Vector2Int(int x, int y)
		:x(x), y(y)
	{

	}
	Vector2Int& operator=(const Vector2Int& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	bool operator==(const Vector2Int& v) const
	{
		return x == v.x && y == v.y;
	}
	Vector2Int operator+(const Vector2Int& v) const
	{
		return Vector2Int(x + v.x, y + v.y);
	}
	Vector2Int operator-() const
	{
		return Vector2Int(-x, -y);
	}
	Vector2Int operator-(const Vector2Int& v) const
	{
		return Vector2Int(x - v.x, y - v.y);
	}
	Vector2Int operator*(int i) const
	{
		return Vector2Int(i * x, i * y);
	}

	int SqrMagnitude() const
	{
		return x * x + y * y;
	}
};

inline Vector2Int operator*(int i, const Vector2Int& v)
{
	return Vector2Int(i * v.x, i * v.y);
}
inline std::ostream& operator<<(std::ostream& stream, const Vector2Int& v)
{
	stream << "(" << v.x << "," << v.y << ")";
	return stream;
}

namespace std
{
	template <>
	struct hash<Vector2Int>
	{
		size_t operator()(const Vector2Int& v) const
		{
			return hash<int>()(v.x) ^ hash<int>()((v.y));
		}
	};
}
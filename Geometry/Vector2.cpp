#include "Vector2.h"
#include<string>

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::Down = Vector2(0.0f, -1.0f);
const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);

Vector2 Vector2::FromString(std::string s)
{
	auto ss = VectorUtility::SplitVector(s);
	float x = std::stof(ss[0]);
	float y = std::stof(ss[1]);
	return Vector2(x, y);
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
	return a + t * (b - a);
}
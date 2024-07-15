#include "Vector3.h"
#include<string>

const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f);
const Vector3 Vector3::One = Vector3(1.0f, 1.0f);
const Vector3 Vector3::Up = Vector3(0.0f, 1.0f);
const Vector3 Vector3::Down = Vector3(0.0f, -1.0f);
const Vector3 Vector3::Right = Vector3(1.0f, 0.0f);
const Vector3 Vector3::Left = Vector3(-1.0f, 0.0f);
const Vector3 Vector3::Front = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Back = Vector3(0.0f, 0.0f, -1.0f);

Vector3 Vector3::FromString(std::string s)
{
	auto ss = VectorUtility::SplitVector(s);
	float x = std::stof(ss[0]);
	float y = std::stof(ss[1]);
	float z = std::stof(ss[2]);
	return Vector3(x, y, z);
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
	return a + t * (b - a);
}
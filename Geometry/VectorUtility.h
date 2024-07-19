#pragma once
#include<iostream>
#include<vector>
#include<string>

namespace Tools
{
	class Vector2;
	class Vector2Int;

	struct VectorUtility
	{
		static double _2PI;
		static std::vector<std::string> SplitVector(std::string s);
		static double ToAngle(Vector2 v);
		static double ToAngle(Vector2Int v);
		static double ClampAngle(double angle);
	};
}
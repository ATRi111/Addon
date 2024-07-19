#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include<unordered_set>
#include<chrono>
#include<random>
#include"Vector2.h"
#include"VectorUtility.h"

namespace Tools
{
	class PolygonGenerator
	{
		static std::mt19937 engine;
	public:
		void Generate(Vector2* vertices, int vertexCount, float xMin, float xMax, float yMin, float yMax);
	};

	struct PolarityComparer
	{
		Vector2 center;
		PolarityComparer(Vector2 center);
		bool Compare(Vector2 a, Vector2 b) const;
	};
}
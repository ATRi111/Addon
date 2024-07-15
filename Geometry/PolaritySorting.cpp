#include "PolaritySorting.h"

void PolygonGenerator::Generate(Vector2* vertices, int vertexCount, float xMin, float xMax, float yMin, float yMax)
{

}

PolarityComparer::PolarityComparer(Vector2 center)
	:center(center)
{
}

bool PolarityComparer::Compare(Vector2 a, Vector2 b) const
{
	double aa = VectorUtility::ToAngle(a - center);
	double ab = VectorUtility::ToAngle(b - center);
	return aa < ab;
}

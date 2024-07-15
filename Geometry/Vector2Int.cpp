#include "Vector2Int.h"

const Vector2Int Vector2Int::Zero = Vector2Int(0, 0);
const Vector2Int Vector2Int::One = Vector2Int(1, 1);
const Vector2Int Vector2Int::Up = Vector2Int(0, 1);
const Vector2Int Vector2Int::Down = Vector2Int(0, -1);
const Vector2Int Vector2Int::Right = Vector2Int(1, 0);
const Vector2Int Vector2Int::Left = Vector2Int(-1, 0);

Vector2Int Vector2Int::FromString(std::string s)
{
	auto ss = VectorUtility::SplitVector(s);
	int x = std::stoi(ss[0]);
	int y = std::stoi(ss[1]);
	return Vector2Int(x, y);
}
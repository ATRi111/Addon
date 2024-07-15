#define _USE_MATH_DEFINES
#include"VectorUtility.h"
#include"Vector2.h"
#include"Vector2Int.h"
using namespace std;

double VectorUtility::_2PI = 2 * M_PI;
vector<string> VectorUtility::SplitVector(string s)
{
	if (!isdigit(s[0]))
		s = s.substr(1, s.length() - 2);
	vector<string> ret;
	size_t i = s.find_first_of(',');
	while (i != string::npos)
	{
		ret.emplace_back(s.substr(0, i));
		if (i + 1 >= s.length())
		{
			s = "";
			break;
		}
		else
			s = s.substr(i + 1);
		i = s.find_first_of(',');
	}
	if (s != "")
	{
		ret.push_back(s);
	}
	return ret;
}

double VectorUtility::ToAngle(Vector2 v)
{
	double angle = -atan2(v.x, v.y); 
	return ClampAngle(angle);
}

double VectorUtility::ToAngle(Vector2Int v)
{
	double angle = -atan2(v.x, v.y);
	return ClampAngle(angle);
}

double VectorUtility::ClampAngle(double angle)
{
	angle += _2PI;
	int i = (int)(angle / _2PI);
	angle -= i * _2PI;
	return angle;
}
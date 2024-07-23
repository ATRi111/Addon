#pragma once
#include"ILerp.h"
#include<string>

namespace Tools
{
	struct DefaultLerp : ILerp<float>
	{
		float Value(float origin, float target, float percent, float time, float duration) override
		{
			return 0.0f;
		}
	};

	struct CurrentTime : ILerp<float>
	{
		float Value(float origin, float target, float percent, float time, float duration) override
		{
			return time;
		}
	};

	struct FloatLerp : ILerp<float>
	{
		float Value(float origin, float target, float percent, float time, float duration)
		{
			return origin + (target - origin) * percent;
		}
	};

	struct StringLerp : ILerp<std::string>
	{
		std::string Value(std::string origin, std::string target, float percent, float time, float duration)
		{
			long size = lroundf(percent * target.size());
			return target.substr(0, size);
		}
	};
}
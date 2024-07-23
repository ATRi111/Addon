#pragma once
#include"ILerp.h"

namespace Tools
{
	class DefaultLerp : ILerp<float>
	{
	public:
		float Value(float origin, float target, float percent, float time, float duration) override
		{
			return 0.0f;
		}
	};

	class CurrentTime : ILerp<float>
	{
	public:
		float Value(float origin, float target, float percent, float time, float duration) override
		{
			return time;
		}
	};
}
#pragma once

namespace Tools
{
	template<typename TValue>
	class ILerp
	{
	public:
		virtual TValue Value(TValue origin, TValue target, float percent, float time, float duration) = 0;
	};
}
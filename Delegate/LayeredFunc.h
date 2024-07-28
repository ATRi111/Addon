#pragma once
#include"Func.h"

namespace Tools
{
	template<typename ... Args>
	class LayeredFunc
	{
		IFunc<bool, Args...>* F;
	public:
		//higher layer has greater layerValue
		int layerValue;

		static bool Comparer(const LayeredFunc<Args...>& a, const LayeredFunc<Args...>& b)
		{
			return a.layerValue > b.layerValue;
		}

		LayeredFunc(int layerValue, bool(*F)(Args...))
			:layerValue(layerValue),F(new StaticFunc<bool, Args...>(F))
		{
		}
		template<typename I>
		LayeredFunc(int layerValue, I* instancePtr, bool(I::* F)(Args...))
			:layerValue(layerValue),F(new MemberFunc<bool, Args...>(instancePtr, F))
		{
		}
		~LayeredFunc()
		{
			delete F;
		}

		bool Invoke(Args... args) const
		{
			return F->Invoke(args...);
		}

		bool Equal(bool(*F)(Args...))
		{
			return this->F->Equal(F);
		}
		template<typename I>
		bool Equal(I* instancePtr, bool(I::* F)(Args...))
		{
			return this->F->Equal(instancePtr, F);
		}
	};
}
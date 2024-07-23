#pragma once
#include"DelegateHeader.h"
#include<unordered_map>
#include<iostream>

namespace Tools
{
	class GameCycleBase
	{
	protected:
		Action<float> cycle;
		Action<float> temp;
	public:
		virtual void Update(float deltaTime)
		{
			temp.MoveTo(cycle);
			cycle.Invoke(deltaTime);
		}
		void AttachToGameCycle(void(*CallBack)(float))
		{
			temp.Add(CallBack);
		}
		template<typename I>
		void AttachToGameCycle(I* instancePtr, void(I::* CallBack)(float))
		{
			temp.Add(instancePtr, CallBack);
		}

		void RemoveFromGameCycle(void(*CallBack)(float))
		{
			temp.Remove(CallBack);
		}
		template<typename I>
		void RemoveFromGameCycle(I* instancePtr, void(I::* CallBack)(float))
		{
			temp.Remove(instancePtr, CallBack);
		}
	};
}

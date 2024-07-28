#pragma once
#include"DelegateHeader.h"
#include<unordered_map>
#include<iostream>

namespace Tools
{
	class GameCycleBase
	{
	protected:
		ActionList<float> Cycle;
		ActionList<float> WaitForAdd;
	public:
		virtual void Update(float deltaTime)
		{
			WaitForAdd.MoveTo(Cycle);
			Cycle.Invoke(deltaTime);
		}
		void AttachToGameCycle(void(*CallBack)(float))
		{
			WaitForAdd.Add(CallBack);
		}
		template<typename I>
		void AttachToGameCycle(I* instancePtr, void(I::* CallBack)(float))
		{
			WaitForAdd.Add(instancePtr, CallBack);
		}

		void RemoveFromGameCycle(void(*CallBack)(float))
		{
			if (!WaitForAdd.Remove(CallBack))
			{
				Cycle.Remove(CallBack);
			}
		}
		template<typename I>
		void RemoveFromGameCycle(I* instancePtr, void(I::* CallBack)(float))
		{
			if (!WaitForAdd.Remove(instancePtr, CallBack))
			{
				Cycle.Remove(instancePtr, CallBack);
			}
		}
	};
}

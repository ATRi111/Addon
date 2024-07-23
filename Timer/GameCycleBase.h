#pragma once
#include"DelegateHeader.h"
#include<unordered_map>

namespace Tools
{
	enum EInvokeTiming
	{
		Update,
	};

	class GameCycleBase
	{
	protected:
		float deltaTime;
		std::unordered_map<EInvokeTiming, Action<float>> cycle;
		std::unordered_map<EInvokeTiming, Action<float>> temp;
		virtual void Update()
		{
			for (auto& pair : temp)
			{
				cycle.insert(std::move(pair));
			}
			temp.clear();
			cycle[EInvokeTiming::Update].Invoke(deltaTime);
		}
	public:
		GameCycleBase(float deltaTime)
			:deltaTime(deltaTime)
		{

		}
		void AttachToGameCycle(void(*CallBack)(float), EInvokeTiming timing = EInvokeTiming::Update)
		{
			temp[timing].Add(CallBack);
		}
		template<typename I>
		void AttachToGameCycle(I* instancePtr, void(I::* CallBack)(float), EInvokeTiming timing = EInvokeTiming::Update)
		{
			temp[timing].Add(instancePtr, &I::CallBack);
		}

		void RemoveFromGameCycle(void(*CallBack)(float), EInvokeTiming timing = EInvokeTiming::Update)
		{
			temp[timing].Remove(CallBack);
		}
		template<typename I>
		void RemoveFromGameCycle(I* instancePtr, void(I::* CallBack)(float), EInvokeTiming timing = EInvokeTiming::Update)
		{
			temp[timing].Remove(instancePtr, &I::CallBack);
		}
	};
}

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
		std::unordered_map<EInvokeTiming, Action<>> cycle;
		std::unordered_map<EInvokeTiming, Action<>> temp;
		virtual void Update()
		{
			for (auto& pair : temp)
			{
				cycle.insert(std::move(pair));
			}
			temp.clear();
			cycle[EInvokeTiming::Update].Invoke();
		}
	public:
		GameCycleBase()
		{

		}

		void AttachToGameCycle(void(*CallBack)(), EInvokeTiming timing = EInvokeTiming::Update)
		{
			temp[timing].Add(CallBack);
		}
		template<typename I>
		void AttachToGameCycle(I* instancePtr, void(I::* CallBack)(), EInvokeTiming timing = EInvokeTiming::Update)
		{
			temp[timing].Add(instancePtr, &I::CallBack);
		}

		void RemoveFromGameCycle(void(*CallBack)(), EInvokeTiming timing = EInvokeTiming::Update)
		{
			temp[timing].Remove(CallBack);
		}
		template<typename I>
		void RemoveFromGameCycle(I* instancePtr, void(I::* CallBack)(), EInvokeTiming timing = EInvokeTiming::Update)
		{
			temp[timing].Remove(instancePtr, &I::CallBack);
		}
	};
}

#pragma once
#include"LayeredFunc.h"
#include<list>

namespace Tools
{
	//a list of IAction 
	template<typename ... Args>
	class LayeredFuncList
	{
		//this class takes ownership of funcs; do not try to add existing pointer into funcs
		std::list<LayeredFunc<Args...>> funcs;
	public:
		LayeredFuncList()
		{
			funcs = std::list<LayeredFunc<Args...>>();
		}
		~LayeredFuncList()
		{

		}

		void Invoke(Args... args)
		{
			typename std::list<LayeredFunc<Args...>>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); )
			{
				LayeredFunc<Args...>& a = *it;
				it++;	//a might remove itself while being invoked 
				if (a.Invoke(args...))
					break;	//interrupted
			}
		}

		void Add(int layerValue, bool(*F)(Args...))
		{
			funcs.emplace_back(layerValue, F);
			funcs.sort(LayeredFunc<Args...>::Comparer);
		}
		template<typename I>
		void Add(int layerValue, I* instancePtr, bool(I::* F)(Args...))
		{
			funcs.emplace_back(layerValue, instancePtr, F);
			funcs.sort(LayeredFunc<Args...>::Comparer);
		}

		//WARN: it is dangerous for an IFunc to call Remove;
		//an IFunc can only remove ITSELF from LayeredFuncList
		bool Remove(void(*F)(Args...))
		{
			typename std::list<LayeredFunc<Args...>>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); it++)
			{
				if (it->Equal(F))
				{
					funcs.erase(it);
					return true;
				}
			}
			return false;
		}
		//WARN: it is dangerous for an IAction to call Remove;
		//an IAction can only remove ITSELF from LayeredFuncList
		template<typename I>
		bool Remove(I* instancePtr, bool(I::* F)(Args...))
		{
			typename std::list<LayeredFunc<Args...>>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); it++)
			{
				if (it->Equal(instancePtr, F))
				{
					funcs.erase(it);
					return true;
				}
			}
			return false;
		}
		void Clear()
		{
			funcs.clear();
		}
		int Count() const
		{
			return funcs.size();
		}
	};
}
#pragma once
#include"IAction.h"
#include"Delegate.h"
#include<list>

namespace Tools
{
	//a list of IAction 
	template<typename ... Args>
	class Action : public Delegate
	{
		//this class takes ownership of funcs; do not try to add existing pointer into funcs
		std::list<IAction<Args...>*> funcs;
	public:
		Action()
		{
			funcs = std::list<IAction<Args...>*>();
		}
		void Invoke(Args... args)
		{
			for (IAction<Args...>* F : funcs)
			{
				F->Invoke(args...);
			}
		}

		void Add(void(*F)(Args...))
		{
			StaticAction<Args...>* p = new StaticAction<Args...>(F);
			funcs.push_back(p);
		}
		template<typename I>
		void Add(I* instancePtr, void(I::* F)(Args...))
		{
			MemberAction<I, Args...>* p = new MemberAction<I, Args...>(instancePtr, F);
			funcs.push_back(p);
		}
		bool Remove(void(*F)(Args...))
		{
			StaticAction<Args...> S = StaticAction<Args...>(F);
			typename std::list<IAction<Args...>*>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); it++)
			{
				if ((*it)->Equal(S))
				{
					delete* it;
					funcs.erase(it);
					return true;
				}
			}
			return false;
		}
		template<typename I>
		bool Remove(I* instancePtr, void(I::* F)(Args...))
		{
			MemberAction<I, Args...> M(instancePtr, F);
			typename std::list<IAction<Args...>*>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); it++)
			{
				if ((*it)->Equal(M))
				{
					delete* it;
					funcs.erase(it);
					return true;
				}
			}
			return false;
		}
		void Clear()
		{
			for (IAction<Args...>* p : funcs)
			{
				delete p;
			}
			funcs.clear();
		}
		int Count()
		{
			return funcs.size();
		}
		~Action()
		{
			for (IAction<Args...>* p : funcs)
			{
				delete p;
			}
		}
	};
}

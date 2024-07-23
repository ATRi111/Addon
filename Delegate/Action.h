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
		//this class takes ownership of actions; do not try to add existing pointer into actions
		std::list<IAction<Args...>*> actions;
	public:
		Action()
		{
			actions = std::list<IAction<Args...>*>();
		}
		void Invoke(Args... args)
		{
			for (IAction<Args...>* F : actions)
			{
				F->Invoke(args...);
			}
		}

		void Add(void(*F)(Args...))
		{
			StaticAction<Args...>* p = new StaticAction<Args...>(F);
			actions.push_back(p);
		}
		template<typename I>
		void Add(I* instancePtr, void(I::* F)(Args...))
		{
			MemberAction<I, Args...>* p = new MemberAction<I, Args...>(instancePtr, F);
			actions.push_back(p);
		}
		
		void MoveTo(Action<Args ...>& other)
		{
			for (IAction<Args...>* p : actions)
			{
				other.actions.push_back(p);
			}
			actions.clear();
		}

		bool Remove(void(*F)(Args...))
		{
			StaticAction<Args...> S = StaticAction<Args...>(F);
			typename std::list<IAction<Args...>*>::iterator it;
			for (it = actions.begin(); it != actions.end(); it++)
			{
				if ((*it)->Equal(S))
				{
					delete* it;
					actions.erase(it);
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
			for (it = actions.begin(); it != actions.end(); it++)
			{
				if ((*it)->Equal(M))
				{
					delete* it;
					actions.erase(it);
					return true;
				}
			}
			return false;
		}
		void Clear()
		{
			for (IAction<Args...>* p : actions)
			{
				delete p;
			}
			actions.clear();
		}
		int Count()
		{
			return actions.size();
		}
		~Action()
		{
			for (IAction<Args...>* p : actions)
			{
				delete p;
			}
		}
	};
}

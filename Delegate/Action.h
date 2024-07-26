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

		~Action()
		{
			for (IAction<Args...>* p : actions)
			{
				delete p;
			}
		}

		void Invoke(Args... args)
		{
			typename std::list<IAction<Args...>*>::iterator it;
			for (it = actions.begin(); it != actions.end(); )
			{
				IAction<Args...>*  p = *it;
				it++;	//p might remove itself while being invoked 
				p->Invoke(args...);
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
		//WARN: it is dangerous for an IAction to call Remove;
		//an IAction can only remove ITSELF from Action
		bool Remove(void(*F)(Args...))
		{
			StaticAction<Args...> S = StaticAction<Args...>(F);
			typename std::list<IAction<Args...>*>::iterator it;
			for (it = actions.begin(); it != actions.end(); it++)
			{
				if ((*it)->Equal(S))
				{
					delete (*it);
					actions.erase(it);
					return true;
				}
			}
			return false;
		}
		//WARN: it is dangerous for an IAction to call Remove;
		//an IAction can only remove ITSELF from Action
		template<typename I>
		bool Remove(I* instancePtr, void(I::* F)(Args...))
		{
			MemberAction<I, Args...> M(instancePtr, F);
			typename std::list<IAction<Args...>*>::iterator it;
			for (it = actions.begin(); it != actions.end(); it++)
			{
				if ((*it)->Equal(M))
				{
					delete (*it);
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
		int Count() const
		{
			return actions.size();
		}
	};
}

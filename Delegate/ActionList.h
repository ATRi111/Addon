#pragma once
#include"Delegate.h"
#include"Action.h"
#include<list>

namespace Tools
{
	template<typename ... Args>
	class ActionList : public Delegate
	{
		//this class takes ownership of funcs; do not try to add existing pointer into funcs
		std::list<IAction<Args...>*> actions;
	public:
		ActionList()
		{
			actions = std::list<IAction<Args...>*>();
		}

		~ActionList()
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
		
		void MoveTo(ActionList<Args ...>& other)
		{
			for (IAction<Args...>* p : actions)
			{
				other.actions.push_back(p);
			}
			actions.clear();
		}
		//WARN: it is dangerous for an IAction to call Remove;
		//an IAction can only remove ITSELF from ActionList
		bool Remove(void(*F)(Args...))
		{
			typename std::list<IAction<Args...>*>::iterator it;
			for (it = actions.begin(); it != actions.end(); it++)
			{
				if ((*it)->Equal(F))
				{
					delete (*it);
					actions.erase(it);
					return true;
				}
			}
			return false;
		}
		//WARN: it is dangerous for an IAction to call Remove;
		//an IAction can only remove ITSELF from ActionList
		template<typename I>
		bool Remove(I* instancePtr, void(I::* F)(Args...))
		{
			MemberAction<I, Args...> M(instancePtr, F);
			typename std::list<IAction<Args...>*>::iterator it;
			for (it = actions.begin(); it != actions.end(); it++)
			{
				if ((*it)->Equal(instancePtr, F))
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

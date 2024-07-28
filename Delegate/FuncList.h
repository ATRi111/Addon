#pragma once
#include"Func.h"
#include"Delegate.h"
#include<list>

namespace Tools
{
	template<typename TResult, typename ... Args>
	class FuncList : public Delegate
	{
		//this class takes ownership of funcs; do not try to add existing pointer into funcs
		std::list<IFunc<TResult, Args...>*> funcs;
	public:
		FuncList()
		{
			funcs = std::list<IFunc<TResult, Args...>*>();
		}
		void Invoke(Args... args)
		{
			typename std::list<IFunc<TResult, Args...>*>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); )
			{
				IFunc<TResult, Args...>* p = *it;
				it++;	//p might remove itself while being invoked
				p->Invoke(args...);
			}
		}
		//get the return value of the first element in funcs
		TResult operator()(Args... args)
		{
			return (*funcs.begin())->Invoke(args...);
		}

		void Add(TResult(*F)(Args...))
		{
			StaticFunc<TResult, Args...>* p = new StaticFunc<TResult, Args...>(F);
			funcs.push_back(p);
		}
		template<typename I>
		void Add(I* instancePtr, TResult(I::* F)(Args...))
		{
			MemberFunc<I, TResult, Args...>* p = new MemberFunc<I, TResult, Args...>(instancePtr, F);
			funcs.push_back(p);
		}

		void MoveTo(FuncList<TResult, Args ...>& other)
		{
			for (IFunc<TResult, Args...>* p : funcs)
			{
				other.funcs.push_back(p);
			}
			funcs.clear();
		}
		//WARN: it is dangerous for an IFunc to call Remove;
		//an IFunc can only remove ITSELF from FuncList
		bool Remove(TResult(*F)(Args...))
		{
			typename std::list<IFunc<TResult, Args...>*>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); it++)
			{
				if ((*it)->Equal(F))
				{
					delete (*it);
					funcs.erase(it);
					return true;
				}
			}
			return false;
		}
		//WARN: it is dangerous for an IFunc to call Remove;
		//an IFunc can only remove ITSELF from FuncList
		template<typename I>
		bool Remove(I* instancePtr, TResult(I::* F)(Args...))
		{
			typename std::list<IFunc<TResult, Args...>*>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); it++)
			{
				if ((*it)->Equal(instancePtr, F))
				{
					delete (*it);
					funcs.erase(it);
					return true;
				}
			}
			return false;
		}
		void Clear()
		{
			for (IFunc<TResult, Args...>* p : funcs)
			{
				delete p;
			}
			funcs.clear();
		}
		int Count() const
		{
			return funcs.size();
		}
		~FuncList()
		{
			for (IFunc<TResult, Args...>* p : funcs)
			{
				delete p;
			}
		}
	};
}
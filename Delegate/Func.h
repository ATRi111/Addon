#pragma once
#include"IFunc.h"
#include"Delegate.h"
#include<list>

namespace Tools
{
	//a list of IFunc 
	template<typename TResult, typename ... Args>
	class Func : public Delegate
	{
		//this class takes ownership of funcs; do not try to add existing pointer into funcs
		std::list<IFunc<TResult, Args...>*> funcs;
	public:
		Func()
		{
			funcs = std::list<IFunc<TResult, Args...>>();
		}
		TResult Invoke(Args... args)
		{
			for (IFunc<TResult, Args...> F : funcs)
			{
				F.Invoke(args...);
			}
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
		bool Remove(TResult(*F)(Args...))
		{
			StaticFunc<TResult, Args...> F = StaticFunc<TResult, Args...>(F);
			typename std::list<IFunc<TResult, Args...>*>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); it++)
			{
				if (*it->Equal(F))
				{
					delete *it;
					funcs.erase(it);
					return true;
				}
			}
			return false;
		}
		template<typename I>
		bool Remove(I* instancePtr, TResult(I::* F)(Args...))
		{
			MemberFunc<I, TResult, Args...> F = MemberFunc<I, TResult, Args...>(F);
			typename std::list<IFunc<TResult, Args...>*>::iterator it;
			for (it = funcs.begin(); it != funcs.end(); it++)
			{
				if (*it->Equal(F))
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
			for (IFunc<TResult, Args...>* p : funcs)
			{
				delete p;
			}
			funcs.clear();
		}
		int Count()
		{
			return funcs.size();
		}

		~Func()
		{
			for (IFunc<TResult, Args...>* p : funcs)
			{
				delete p;
			}
		}
	};
}